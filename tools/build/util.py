"""Small helpers shared by the build steps."""

import os
import re
import sys


class BuildError(Exception):
    """A configuration or environment problem that stops the build."""


# --------------------------------------------------------------------------
# Console output
# --------------------------------------------------------------------------

_COLORS = {"red": 31, "green": 32, "yellow": 33, "cyan": 36}
_use_color = sys.stdout.isatty() and "NO_COLOR" not in os.environ
if _use_color and os.name == "nt":
    os.system("")  # enables ANSI escape processing in the Windows console

verbose = False


def say(text: str = "", color: str | None = None) -> None:
    if color and _use_color:
        text = f"\x1b[{_COLORS[color]}m{text}\x1b[0m"
    print(text, flush=True)


def debug(text: str) -> None:
    if verbose:
        say(text)


# --------------------------------------------------------------------------
# Command lines and paths
# --------------------------------------------------------------------------


def quote(s: str) -> str:
    """Quotes an argument for a Windows command line if it needs it."""
    if s == "" or re.search(r'[\s"]', s):
        return '"' + s.replace('"', '\\"') + '"'
    return s


def split_list(s: str | None, sep: str = r"[,;]") -> list[str]:
    if not s:
        return []
    return [p.strip() for p in re.split(sep, s) if p.strip()]


def expand_macros(s: str) -> str:
    """Expands $(VAR) from the environment, as Visual Studio does for unknown macros."""

    def repl(m: re.Match) -> str:
        val = os.environ.get(m.group(1))
        if val is None:
            raise BuildError(f"Unknown macro {m.group(0)} in project file.")
        return val

    return re.sub(r"\$\(([^)]+)\)", repl, s)


def resolve_proj_path(proj_dir: str, p: str) -> str:
    p = expand_macros(p).strip()
    full = os.path.normpath(os.path.join(proj_dir, p))
    # Keep a trailing separator, like .NET's Path.GetFullPath, so command lines stay stable.
    if p.endswith(("\\", "/")) and not full.endswith("\\"):
        full += "\\"
    return full


def startswith_i(s: str, prefix: str) -> bool:
    return s.lower().startswith(prefix.lower())


# --------------------------------------------------------------------------
# File timestamps, cached between compile/link steps
# --------------------------------------------------------------------------

_mtimes: dict[str, int | None] = {}


def mtime(path: str) -> int | None:
    if path not in _mtimes:
        try:
            _mtimes[path] = os.stat(path).st_mtime_ns
        except OSError:
            _mtimes[path] = None
    return _mtimes[path]


def clear_mtimes() -> None:
    _mtimes.clear()


def read_text(path: str) -> str | None:
    try:
        with open(path, encoding="utf-8", newline="") as f:
            return f.read()
    except OSError:
        return None


def write_text(path: str, text: str) -> None:
    with open(path, "w", encoding="utf-8", newline="") as f:
        f.write(text)


def remove(path: str) -> None:
    try:
        os.remove(path)
    except OSError:
        pass
