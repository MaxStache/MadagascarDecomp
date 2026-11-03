"""Linking static libraries and the executable.

link.exe runs from a response file `<output>.rsp`; the output is up to date when
that file's contents are unchanged and no input is newer than the output.
"""

import os
import subprocess

from . import util
from .toolchain import Toolchain
from .util import quote, resolve_proj_path, say, split_list
from .vcproj import Project

# Libraries every VS2003 linker configuration inherits unless it sets $(NoInherit).
INHERITED_LIBS = ["kernel32.lib", "user32.lib", "gdi32.lib", "winspool.lib", "comdlg32.lib", "advapi32.lib",
                  "shell32.lib", "ole32.lib", "oleaut32.lib", "uuid.lib", "odbc32.lib", "odbccp32.lib"]


def _link(tc: Toolchain, output: str, args: list[str], inputs: list[str], cwd: str,
          mode: list[str] | None = None) -> bool:
    rsp = output + ".rsp"
    body = "\r\n".join(args)
    out_time = util.mtime(output)
    if out_time is not None and util.read_text(rsp) == body:
        if not any((t := util.mtime(i)) is not None and t > out_time for i in inputs):
            say("  (up to date)")
            return True

    os.makedirs(os.path.dirname(output), exist_ok=True)
    util.write_text(rsp, body)
    util.debug(f"link @{rsp}\n{body}")
    result = subprocess.run([tc.link, *(mode or []), "@" + rsp], cwd=cwd, env=tc.env,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
    for line in result.stdout.splitlines():
        # The toolkit's CRT libraries reference a libcmt.pdb it does not ship;
        # this linker cannot /IGNORE the warning.
        if "LNK4099" not in line:
            say(f"    {line}")
    if result.returncode != 0:
        util.remove(rsp)
        return False
    say(f"  -> {output}")
    return True


def build_library(tc: Toolchain, proj: Project) -> bool:
    # The toolkit has no lib.exe; "link /lib" is the same tool (/lib must come first).
    objs = [u.obj for u in proj.units]
    args = ["/nologo", "/OUT:" + quote(proj.output)] + [quote(o) for o in objs]
    return _link(tc, proj.output, args, objs, proj.dir, ["/lib"])


def build_executable(tc: Toolchain, proj: Project, dep_libs: list[str], st_debug_crt: bool,
                     pdb_objs: list[str] | None = None, keep_unused: bool = False) -> bool:
    """pdb_objs: link a PDB for a configuration without debug info, adding these objects.
    keep_unused: keep unreferenced functions (identical ones are still folded, like the original)."""
    l = proj.linker
    a = ["/OUT:" + quote(proj.output)]
    if (l.get("SuppressStartupBanner") or "").upper() == "TRUE":
        a.append("/nologo")
    a += {"1": ["/INCREMENTAL:NO"], "2": ["/INCREMENTAL"]}.get(l.get("LinkIncremental"), [])
    debug = (l.get("GenerateDebugInformation") or "").upper() == "TRUE"
    pdb = pdb_objs is not None
    if debug or pdb:
        a.append("/DEBUG")
    if keep_unused:
        a += ["/OPT:NOREF", "/OPT:ICF"]
    if pdb and not debug:
        if not keep_unused:
            # /DEBUG turns off unreferenced-code removal and identical-code folding;
            # keep the release layout.
            a += ["/OPT:REF", "/OPT:ICF"]
        a.append("/PDB:" + quote(os.path.splitext(proj.output)[0] + ".pdb"))
    elif l.get("ProgramDatabaseFile"):
        a.append("/PDB:" + quote(resolve_proj_path(proj.dir, l["ProgramDatabaseFile"])))
    a += {"1": ["/SUBSYSTEM:CONSOLE"], "2": ["/SUBSYSTEM:WINDOWS"]}.get(l.get("SubSystem"), [])
    a.append("/MACHINE:X86")
    a += ["/LIBPATH:" + quote(resolve_proj_path(proj.dir, d)) for d in split_list(l.get("AdditionalLibraryDirectories"))]
    a += ["/NODEFAULTLIB:" + n for n in split_list(l.get("IgnoreDefaultLibraryNames"))]
    if st_debug_crt:
        # Prebuilt libraries (RenderWare debug libs) and /MTd dependency projects
        # still request the MT debug CRT, even when this project itself is /MT.
        a += ["/NODEFAULTLIB:libcmtd.lib", "/NODEFAULTLIB:libcpmtd.lib"]
    a += split_list(l.get("AdditionalOptions"), r"\s+")
    objs = [u.obj for u in proj.units] + (pdb_objs or [])
    a += [quote(o) for o in objs]
    a += [quote(d) for d in dep_libs]
    a += split_list(l.get("AdditionalDependencies"), r"\s+") + INHERITED_LIBS
    return _link(tc, proj.output, a, objs + dep_libs, proj.dir)
