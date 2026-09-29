"""Incremental, parallel compilation of a project's translation units.

Each object gets a `<obj>.d` file next to it: the first line is the exact cl
command line, the rest are the source and every non-system header it included
(from /showIncludes). An object is rebuilt when the command changes or any of
those files is newer than it.
"""

import os
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass

from . import util
from .toolchain import Toolchain
from .util import quote, say
from .vcproj import Project, Unit

_INCLUDE_NOTE = "Note: including file:"


@dataclass
class Task:
    unit: Unit
    cmd: str


def _dep_file(unit: Unit) -> str:
    return unit.obj + ".d"


def _up_to_date(task: Task) -> bool:
    obj_time = util.mtime(task.unit.obj)
    lines = (util.read_text(_dep_file(task.unit)) or "").splitlines()
    if obj_time is None or not lines or lines[0] != task.cmd:
        return False
    for dep in lines[1:]:
        t = util.mtime(dep)
        if t is None or t > obj_time:
            return False
    return True


def _run_cl(tc: Toolchain, task: Task, cwd: str) -> subprocess.CompletedProcess:
    util.debug(f"cl {task.cmd}")
    return subprocess.run(f'"{tc.cl}" {task.cmd}', cwd=cwd, env=tc.env,
                          capture_output=True, text=True, errors="replace")


def _finish(tc: Toolchain, proj: Project, task: Task, result: subprocess.CompletedProcess) -> bool:
    unit = task.unit
    name = os.path.basename(unit.source)
    deps = [unit.source]
    msgs = []
    for line in (result.stdout + result.stderr).splitlines():
        if line.startswith(_INCLUDE_NOTE):
            inc = line[len(_INCLUDE_NOTE):].strip()
            if not any(util.startswith_i(inc, p) for p in tc.system_prefixes):
                deps.append(inc)
        elif line.strip() and line.strip() != name:  # cl echoes the file name
            msgs.append(line)
    if unit.uses_pch and proj.pch:
        deps.append(proj.pch)

    if result.returncode == 0:
        say(f"  {name}")
        for m in msgs:
            say(f"    {m}", "yellow")
        lines = [task.cmd] + list(dict.fromkeys(deps))
        util.write_text(_dep_file(unit), "".join(l + "\r\n" for l in lines))
        return True

    say(f"  {name}  FAILED", "red")
    for m in msgs:
        say(f"    {m}", "red")
    util.remove(_dep_file(unit))
    return False


def _compile_all(tc: Toolchain, proj: Project, tasks: list[Task], jobs: int) -> int:
    """Compiles the tasks with up to `jobs` concurrent cl.exe processes; returns the failure count."""
    failed = 0
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        futures = {pool.submit(_run_cl, tc, t, proj.dir): t for t in tasks}
        for fut in as_completed(futures):
            if not _finish(tc, proj, futures[fut], fut.result()):
                failed += 1
    return failed


def build_objects(tc: Toolchain, proj: Project, jobs: int) -> bool:
    os.makedirs(proj.obj_dir, exist_ok=True)
    # Configurations with debug info share one PDB, so they must compile serially.
    if any(u.debug_info for u in proj.units):
        jobs = 1

    def make(u: Unit) -> Task:
        args = ["/c"] + tc.sdk.flags + u.flags + ["/showIncludes", "/Fo" + quote(u.obj), quote(u.source)]
        return Task(u, " ".join(args))

    # The precompiled header must exist before anything that uses it.
    pch_stale = False
    for u in (u for u in proj.units if u.creates_pch):
        t = make(u)
        if not _up_to_date(t) or util.mtime(proj.pch or "") is None:
            pch_stale = True
            if _compile_all(tc, proj, [t], 1):
                return False
            util.clear_mtimes()

    todo = [t for t in map(make, (u for u in proj.units if not u.creates_pch))
            if (pch_stale and t.unit.uses_pch) or not _up_to_date(t)]
    if not todo:
        if not pch_stale:
            say("  (objects up to date)")
        return True

    failed = _compile_all(tc, proj, todo, max(1, jobs))
    util.clear_mtimes()
    if failed:
        say(f"{failed} file(s) failed to compile.", "red")
        return False
    return True
