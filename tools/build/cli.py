"""Command line entry point: `python build.py [configuration] [options]`."""

import argparse
import os
import shutil
import time
import subprocess

from . import compile, link, toolchain, util, vcproj
from .util import BuildError, say

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
WIN32_DIR = os.path.join(ROOT, "src", "console", "game_framework", "win32")

# In dependency order; static libraries are linked into the executable.
PROJECTS = [
    os.path.join(WIN32_DIR, "gfcore", "gfcore.vcproj"),
    os.path.join(ROOT, "src", "console", "plugins", "loading_screen", "win32", "loadingscreen.vcproj"),
    os.path.join(WIN32_DIR, "game_framework", "game_framework.vcproj"),
]

CONFIGURATIONS = [f"{api} {variant}{kind}"
                  for api in ("D3D", "OGL")
                  for variant in ("", "Design ")
                  for kind in ("Debug", "Release", "Metrics")]


def _configuration(s: str) -> str:
    """Accepts "D3D Debug" as well as "d3d-debug" or "d3d_design_release"."""
    key = s.replace("-", " ").replace("_", " ").lower()
    for c in CONFIGURATIONS:
        if c.lower() == key:
            return c
    raise argparse.ArgumentTypeError(f"unknown configuration '{s}' (choose from: {', '.join(CONFIGURATIONS)})")


def parse_args(argv: list[str] | None) -> argparse.Namespace:
    p = argparse.ArgumentParser(prog="build.py", description="Build the Win32 game with the Visual C++ Toolkit 2003.")
    p.add_argument("configuration", nargs="?", type=_configuration, default="D3D Release",
                   help='e.g. "D3D Debug" or d3d-debug (default: D3D Release)')
    p.add_argument("--rebuild", action="store_true", help="delete this configuration's outputs before building")
    p.add_argument("--clean", action="store_true", help="delete this configuration's outputs and stop")
    p.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 1,
                   help="parallel compiles (configurations with debug info always compile serially)")
    p.add_argument("--toolkit-dir", help="Visual C++ Toolkit 2003 root (auto-detected)")
    p.add_argument("--winsdk-dir", help="Windows SDK root: Platform SDK or Windows Kits\\10 (auto-detected)")
    p.add_argument("--rwgsdk", help="RenderWare Graphics SDK root (default: $RWGSDK, then ./rwsdk)")
    p.add_argument("--st-debug-crt", action="store_true",
                   help="build /MTd configurations against the single-threaded debug CRT (/MLd); "
                        "automatic when libcmtd.lib/libcpmtd.lib are not installed")
    p.add_argument("--pdb", action="store_true",
                   help="compile with /Z7 and link a PDB next to the executable; object code is unchanged")
    p.add_argument("--keep-unused", action="store_true",
                   help="link with /OPT:NOREF so unreferenced functions are kept; identical (e.g. empty) "
                        "functions are still folded together (/OPT:ICF), as in the original")
    p.add_argument("-D", "--define", action="append", default=[], metavar="NAME[=VALUE]",
                   help="define a preprocessor macro for every source file, e.g. --define DECOMP_ENABLE_CONSOLE "
                        "(repeatable; changing defines recompiles the affected objects)")
    p.add_argument("-v", "--verbose", action="store_true", help="print compiler and linker command lines")

    p.add_argument("-run", action="store_true", help="run the built program")

    return p.parse_args(argv)


def clean(projects: list[vcproj.Project]) -> None:
    for p in projects:
        shutil.rmtree(p.obj_dir, ignore_errors=True)
        util.remove(p.output)
        util.remove(p.output + ".rsp")


# Options accepted by build(); keys match the argparse destinations.
BUILD_DEFAULTS = {
    "configuration": "D3D Release",
    "rebuild": False,
    "clean": False,
    "jobs": os.cpu_count() or 1,
    "toolkit_dir": None,
    "winsdk_dir": None,
    "rwgsdk": None,
    "st_debug_crt": False,
    "pdb": False,
    "keep_unused": False,
    "define": [],
    "run": False,
}


def build_cli(args: argparse.Namespace) -> bool:
    """Builds from parsed command line arguments."""
    opts = {k: v for k, v in vars(args).items() if k in BUILD_DEFAULTS}
    return build(opts) is not None


def build(options: dict) -> str | None:
    """Builds with the given options; missing keys fall back to BUILD_DEFAULTS.

    Returns the executable's path (buildOutputPath) on success, None on a compile/link failure.
    """
    unknown = set(options) - set(BUILD_DEFAULTS)
    if unknown:
        raise BuildError(f"unknown build option(s): {', '.join(sorted(unknown))}")
    args = argparse.Namespace(**{**BUILD_DEFAULTS, **options})
    args.configuration = _configuration(args.configuration)

    tc = toolchain.setup(ROOT, args.toolkit_dir, args.winsdk_dir, args.rwgsdk)
    auto_st_crt = not tc.has_mt_debug_crt and not args.st_debug_crt
    st_debug_crt = args.st_debug_crt or auto_st_crt

    projects = [vcproj.load(p, args.configuration, st_debug_crt) for p in PROJECTS]
    if args.pdb:
        for p in projects:
            for u in p.units:
                if not u.debug_info:
                    # /Z7 keeps the debug info in each object, so compiles stay parallel.
                    u.flags.append("/Z7")
    if args.define:
        defines = ["/D" + util.quote(d) for d in args.define]
        for p in projects:
            for u in p.units:
                u.flags += defines

    if args.clean or args.rebuild:
        clean(projects)
        say(f"Cleaned [{args.configuration}].")
        if args.clean:
            return projects[-1].output

    say(f"Configuration: {args.configuration}")
    say(f"Compiler:      {tc.toolkit}")
    say(f"Windows SDK:   {tc.sdk.name}")
    say(f"RenderWare SDK:    {tc.rwgsdk}")
    if args.define:
        say(f"Defines:       {' '.join(args.define)}")
    if auto_st_crt and any(p.runtime_library == "1" for p in projects):
        say("Note:          libcmtd.lib/libcpmtd.lib not found; using the single-threaded debug CRT (/MLd).", "yellow")
    start = time.perf_counter()

    dep_libs: list[str] = []
    # With /Z7, PCH users keep their type info in the PCH object, which nothing
    # pulls out of a static library; link those objects in directly.
    pdb_objs: list[str] = []
    for p in projects:
        say(f"\n== {p.name}", "cyan")
        if not compile.build_objects(tc, p, args.jobs):
            say("\nBuild FAILED.", "red")
            return None
        if p.is_library:
            ok = link.build_library(tc, p)
        else:
            ok = link.build_executable(tc, p, dep_libs, st_debug_crt, pdb_objs if args.pdb else None,
                                         args.keep_unused)
        if not ok:
            say(f"\nBuild FAILED ({p.name} link).", "red")
            return None
        if p.is_library:
            dep_libs.append(p.output)
            pdb_objs += [u.obj for u in p.units if u.creates_pch]

    buildOutputPath = projects[-1].output
    say(f"\nBuild succeeded in {time.perf_counter() - start:.1f}s: {buildOutputPath}", "green")

    if args.run:
        say("\nStarting built executable...", "green")
        subprocess.run([buildOutputPath], check=False)

    return buildOutputPath


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    util.verbose = args.verbose
    try:
        return 0 if build_cli(args) else 1
    except BuildError as e:
        say(f"error: {e}", "red")
        return 1
