"""Finds the compiler, Windows SDK and RenderWare SDK, and sets up the environment."""

import os
from dataclasses import dataclass, field

from .util import BuildError


@dataclass
class WinSdk:
    name: str
    include: list[str]
    lib: list[str]
    flags: list[str] = field(default_factory=list)


@dataclass
class Toolchain:
    toolkit: str
    sdk: WinSdk
    rwgsdk: str
    env: dict[str, str]
    # Headers under these directories are not tracked as dependencies.
    system_prefixes: list[str]
    has_mt_debug_crt: bool

    @property
    def cl(self) -> str:
        return os.path.join(self.toolkit, "bin", "cl.exe")

    @property
    def link(self) -> str:
        return os.path.join(self.toolkit, "bin", "link.exe")


def _program_files() -> list[str]:
    return [p for p in (os.environ.get("ProgramFiles(x86)"), os.environ.get("ProgramFiles")) if p]


def find_toolkit(explicit: str | None) -> str:
    candidates = [explicit, os.environ.get("VCToolkitInstallDir")]
    candidates += [os.path.join(p, "Microsoft Visual C++ Toolkit 2003") for p in _program_files()]
    for c in candidates:
        if c and os.path.isfile(os.path.join(c, "bin", "cl.exe")):
            return os.path.abspath(c)
    raise BuildError("Visual C++ Toolkit 2003 not found. Pass --toolkit-dir <path>.")


def _version_key(name: str) -> tuple[int, ...]:
    try:
        return tuple(int(p) for p in name.split("."))
    except ValueError:
        return ()


def find_winsdk(explicit: str | None) -> WinSdk:
    # Era-appropriate Platform SDK: headers work with cl 13.10 unmodified.
    classic = [explicit, os.environ.get("MSSdk")]
    for p in _program_files():
        classic += [os.path.join(p, "Microsoft Platform SDK"),
                    os.path.join(p, "Microsoft Platform SDK for Windows Server 2003 R2")]
    for c in classic:
        if c and os.path.isfile(os.path.join(c, "Include", "windows.h")):
            return WinSdk(f"Platform SDK ({c})", [os.path.join(c, "Include")], [os.path.join(c, "Lib")])

    # Windows 10/11 SDK.
    kits = explicit or os.path.join(os.environ.get("ProgramFiles(x86)", ""), "Windows Kits", "10")
    try:
        names = os.listdir(os.path.join(kits, "Include"))
    except OSError:
        names = []
    versions = sorted(
        (v for v in names
         if os.path.isfile(os.path.join(kits, "Include", v, "um", "windows.h"))
         and os.path.isfile(os.path.join(kits, "Lib", v, "um", "x86", "kernel32.lib"))),
        key=_version_key, reverse=True)
    if not versions:
        raise BuildError("No Windows SDK found. Install the Windows 10/11 SDK (x86 libs) or pass --winsdk-dir <path>.")
    v = versions[0]
    return WinSdk(
        name=f"Windows SDK {v}",
        include=[os.path.join(kits, "Include", v, "um"), os.path.join(kits, "Include", v, "shared")],
        lib=[os.path.join(kits, "Lib", v, "um", "x86")],
        # Keep the modern headers within what cl 13.10 can parse.
        flags=["/D_WIN32_WINNT=0x0501", "/DWINVER=0x0501", "/DNTDDI_VERSION=0x05010000",
               "/DWIN32_LEAN_AND_MEAN",
               "/wd4068",   # unknown pragma
               "/wd4163",   # not available as an intrinsic function
               "/wd4616"])  # #pragma warning: invalid warning number


def find_rwgsdk(explicit: str | None, root: str) -> str:
    rw = explicit or os.environ.get("RWGSDK") or os.path.join(root, "rwsdk")
    if not os.path.isdir(os.path.join(rw, "include")):
        raise BuildError(f"RenderWare SDK not found at '{rw}'. Set RWGSDK or pass --rwgsdk.")
    return os.path.abspath(rw)


def setup(root: str, toolkit_dir: str | None, winsdk_dir: str | None, rwgsdk: str | None) -> Toolchain:
    tk = find_toolkit(toolkit_dir)
    sdk = find_winsdk(winsdk_dir)
    rw = find_rwgsdk(rwgsdk, root)

    # Project files reference $(RWGSDK); it is expanded from our own environment.
    os.environ["RWGSDK"] = rw
    env = dict(os.environ)
    env["PATH"] = os.path.join(tk, "bin") + ";" + env.get("PATH", "")
    env["INCLUDE"] = ";".join([os.path.join(tk, "include")] + sdk.include)
    lib_dirs = [os.path.join(tk, "lib")] + sdk.lib
    env["LIB"] = ";".join(lib_dirs)

    # The free toolkit omits the multithreaded debug CRT; a full VS .NET 2003 install has it.
    has_mt_debug_crt = any(
        os.path.isfile(os.path.join(d, "libcmtd.lib")) and os.path.isfile(os.path.join(d, "libcpmtd.lib"))
        for d in lib_dirs)

    prefixes = [tk + "\\", os.path.dirname(sdk.include[0]) + "\\"]
    return Toolchain(tk, sdk, rw, env, prefixes, has_mt_debug_crt)
