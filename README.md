# MadagascarDecomp
A (Work in Progress) decompilation of Madagascar (2005)

## Building

Requires the Visual C++ Toolkit 2003, a Windows SDK with x86 libraries, the RenderWare Graphics SDK (`./rwsdk` or `$RWGSDK`) and Python 3.10+.

```
python build.py "D3D Debug"      # or d3d-debug; default is "D3D Release"
python build.py d3d-debug --rebuild
python build.py --help
```

The build code lives in `tools/build/`.

## Building on macOS (Wine)

The toolchain runs under Wine in the prefix `~/.wine-vs2003`:

| Component | Location in the prefix |
|---|---|
| Visual C++ Toolkit 2003 (`cl`, `link`, `lib`, `nmake`) | `C:\Program Files (x86)\Microsoft Visual C++ Toolkit 2003` |
| Platform SDK, WS2003 SP1 (Win32 headers, x86 import libs, `rc.exe`) | `C:\PlatformSDK` |
| Python 3.12 (embeddable) — runs the build driver | `C:\Python312` |

```
./build-wine.sh                      # D3D Release
./build-wine.sh d3d-debug --rebuild
./build-wine.sh --help               # all options are passed through to tools/build.py
```

reccmp itself runs natively on macOS (it only shells out to Wine to read the PDB):

```
python3 -m venv .venv && ./.venv/bin/pip install reccmp
cp /path/to/original/Game.exe originals/Game.exe     # sha256 a8dcfe45...
./.venv/bin/reccmp-project detect --search-path ./originals

./reccmp_check.sh                    # build + full report -> report.html
./reccmp_check.sh --no-build         # compare only
./reccmp_check.sh 0x464ef0           # verbose asm diff for one address
./reccmp_check.sh --vtable           # also check vtables
```
