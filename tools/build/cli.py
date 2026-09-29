"""Command line entry point: `python build.py [configuration] [options]`."""

import argparse
import os
import shutil
import time

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
    p.add_argument("-v", "--verbose", action="store_true", help="print compiler and linker command lines")
    return p.parse_args(argv)


def clean(projects: list[vcproj.Project]) -> None:
    for p in projects:
        shutil.rmtree(p.obj_dir, ignore_errors=True)
        util.remove(p.output)
        util.remove(p.output + ".rsp")


def build(args: argparse.Namespace) -> bool:
    tc = toolchain.setup(ROOT, args.toolkit_dir, args.winsdk_dir, args.rwgsdk)
    auto_st_crt = not tc.has_mt_debug_crt and not args.st_debug_crt
    st_debug_crt = args.st_debug_crt or auto_st_crt

    projects = [vcproj.load(p, args.configuration, st_debug_crt) for p in PROJECTS]

    if args.clean or args.rebuild:
        clean(projects)
        say(f"Cleaned [{args.configuration}].")
        if args.clean:
            return True

    say(f"Configuration: {args.configuration}")
    say(f"Compiler:      {tc.toolkit}")
    say(f"Windows SDK:   {tc.sdk.name}")
    say(f"RenderWare:    {tc.rwgsdk}")
    if auto_st_crt and any(p.runtime_library == "1" for p in projects):
        say("Note:          libcmtd.lib/libcpmtd.lib not found; using the single-threaded debug CRT (/MLd).", "yellow")
    start = time.perf_counter()

    dep_libs: list[str] = []
    for p in projects:
        say(f"\n== {p.name}", "cyan")
        if not compile.build_objects(tc, p, args.jobs):
            say("\nBuild FAILED.", "red")
            return False
        if p.is_library:
            ok = link.build_library(tc, p)
        else:
            ok = link.build_executable(tc, p, dep_libs, st_debug_crt)
        if not ok:
            say(f"\nBuild FAILED ({p.name} link).", "red")
            return False
        if p.is_library:
            dep_libs.append(p.output)

    say(f"\nBuild succeeded in {time.perf_counter() - start:.1f}s: {projects[-1].output}", "green")
    return True


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    util.verbose = args.verbose
    try:
        return 0 if build(args) else 1
    except BuildError as e:
        say(f"error: {e}", "red")
        return 1
