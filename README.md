# MadagascarDecomp
A decompilation of Madagascar (2005)

## Building

Requires the Visual C++ Toolkit 2003, a Windows SDK with x86 libraries, the RenderWare Graphics SDK (`./rwsdk` or `$RWGSDK`) and Python 3.10+.

```
python build.py "D3D Debug"      # or d3d-debug; default is "D3D Release"
python build.py d3d-debug --rebuild
python build.py --help
```

The build code lives in `tools/build/`.
