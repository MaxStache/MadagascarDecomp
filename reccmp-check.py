import argparse
import os
import subprocess
import sys
from pathlib import Path

from tools.build.util import BuildError, say

__version__ = "1.1.0"

IS_WINDOWS = sys.platform == "win32"

ROOT = Path(__file__).resolve().parent
BUILD_DIR = ROOT / "src" / "console" / "game_framework" / "win32" / "bin" / "Win32 D3D Release"
GAME_EXE = BUILD_DIR / "Game.exe"
VENV = ROOT / ".venv"
TOTAL = 8244

WINE_BIN = Path.home() / "Applications" / "Wine Staging.app" / "Contents" / "Resources" / "wine" / "bin"


# ---------- environment ----------
def wine_env() -> dict[str, str]:
    env = os.environ.copy()
    env["PATH"] = f"{WINE_BIN}{os.pathsep}{env.get('PATH', '')}"
    env.setdefault("WINEPREFIX", str(Path.home() / ".wine-vs2003"))
    env.setdefault("WINEDEBUG", "-all")
    return env


def run_env() -> dict[str, str] | None:
    return None if IS_WINDOWS else wine_env()


def venv_tool(name: str) -> Path:
    if IS_WINDOWS:
        return VENV / "Scripts" / f"{name}.exe"
    return VENV / "bin" / name


# ---------- build ----------
def build_defines(args: argparse.Namespace) -> list[str]:
    defines = ["WITH_AUDIO"]

    if args.no_audio:
        defines.remove("WITH_AUDIO")

    if args.release:
        return defines

    
    if not args.no_console:
        defines.append("DECOMP_ENABLE_CONSOLE")
    if not args.no_window:
        defines.append("DECOMP_DEBUG_WINDOWED")

    return defines


def do_build(args: argparse.Namespace) -> Path | None:
    defines = build_defines(args)

    if IS_WINDOWS:
        from tools.build.cli import build

        try:
            output = build({"configuration": "D3D Release","pdb": True, "keep_unused": True, "define": defines})
        except BuildError as e:
            say(f"error: {e}", "red")
            return None
        return Path(output) if output else None

    cmd = [str(ROOT / "build-wine.sh"), "--pdb", "--keep-unused"]
    for d in defines:
        cmd += ["--define", d]
    if subprocess.call(cmd, cwd=ROOT) != 0:
        return None
    return GAME_EXE


def run_exe(exe: Path) -> int:
    cmd = [str(exe)] if IS_WINDOWS else [str(WINE_BIN / "wine"), str(exe)]
    p = subprocess.Popen(
        cmd,
        cwd=exe.parent,
        env=run_env(),
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    assert p.stdout

    for line in p.stdout:
        sys.stdout.buffer.write(line)
        sys.stdout.flush()
    return p.wait()


# ---------- commands ----------
def cmd_build(args: argparse.Namespace) -> int:
    output = do_build(args)
    if output is None:
        return 1
    if args.run:
        return run_exe(output)
    return 0


def cmd_check(args: argparse.Namespace) -> int:
    reccmp = venv_tool("reccmp-reccmp")
    if not reccmp.exists():
        say(f"No reccmp in {VENV}. Run: python -m venv .venv && pip install reccmp (inside the venv)", "red")
        return 1
    if not (ROOT / "reccmp-user.yml").exists():
        say("No reccmp-user.yml - see the setup note at the top of reccmp-check.py.", "red")
        return 1

    if not args.no_build:
        say("BUILDING...", "cyan")
        if do_build(args) is None:
            say("BUILD FAILED - skipping reccmp.", "red")
            return 1

    env = run_env()
    say("CHECKING...", "cyan")
    if args.address:
        cmd = [str(reccmp), "--target", "GAME", "--verbose", args.address]
    else:
        cmd = [str(reccmp), "--target", "GAME", "--total", str(TOTAL), "--nolib", "--html", str(ROOT / "report.html")]
    rc = subprocess.call(cmd, cwd=BUILD_DIR, env=env)

    if args.vtable:
        say("CHECKING VTABLES...", "cyan")
        rc = subprocess.call([str(venv_tool("reccmp-vtable")), "--target", "GAME"], cwd=BUILD_DIR, env=env) or rc

    return rc


# ---------- parser ----------
def add_define_args(p: argparse.ArgumentParser) -> None:
    p.add_argument(
        "--release",
        action="store_true",
        help="build without the debug defines (DECOMP_ENABLE_CONSOLE, DECOMP_DEBUG_WINDOWED)",
    )
    p.add_argument("--no-console", action="store_true", help="don't define DECOMP_ENABLE_CONSOLE")
    p.add_argument("--no-window", action="store_true", help="don't define DECOMP_DEBUG_WINDOWED")
    p.add_argument("--no-audio", action="store_true", help="don't define WITH_AUDIO")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="reccmp-check",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("--version", action="version", version=f"%(prog)s {__version__}")

    sub = parser.add_subparsers(dest="command", required=True, metavar="COMMAND")

    p_check = sub.add_parser(
        "check",
        help="(default) build, then compare against the original with reccmp",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    p_check.add_argument("address", nargs="?", help="show a verbose asm diff for this address, e.g. 0x464ef0")
    p_check.add_argument("--vtable", action="store_true", help="also check vtables")
    p_check.add_argument("--no-build", action="store_true", help="skip the build, just compare")
    add_define_args(p_check)
    p_check.set_defaults(func=cmd_check)

    p_build = sub.add_parser(
        "build",
        help="build with --pdb --keep-unused and the debug defines",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    add_define_args(p_build)
    p_build.add_argument("--run", action="store_true", help="run the built executable on success")
    p_build.set_defaults(func=cmd_build)

    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    argv = sys.argv[1:] if argv is None else list(argv)

    if not argv or argv[0] not in ("check", "build", "-h", "--help", "--version"):
        argv = ["build" if "--run" in argv else "check", *argv]
    args = parser.parse_args(argv)

    try:
        return args.func(args)
    except KeyboardInterrupt:
        return 130


if __name__ == "__main__":
    sys.exit(main())
