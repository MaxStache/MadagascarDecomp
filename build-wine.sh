#!/bin/bash
# Build MadagascarDecomp on macOS using the Visual C++ Toolkit 2003 under Wine.
#
#   ./build-wine.sh                          # D3D Release
#   ./build-wine.sh d3d-debug
#   ./build-wine.sh "D3D Release" --rebuild
#   ./build-wine.sh --pdb --keep-unused      # what reccmp wants
#
# Toolchain (installed in the Wine prefix ~/.wine-vs2003):
#   C:\Program Files (x86)\Microsoft Visual C++ Toolkit 2003  cl/link/lib/nmake
#   C:\PlatformSDK                                            Win32 headers + import libs
#   C:\Python312                                              embeddable Python 3.12
set -e

export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-vs2003}"
export WINEDEBUG="${WINEDEBUG:--all}"
WINE="$HOME/Applications/Wine Staging.app/Contents/Resources/wine/bin/wine"
PYTHON='C:\Python312\python.exe'
TOOLKIT='C:\Program Files (x86)\Microsoft Visual C++ Toolkit 2003'
WINSDK='C:\PlatformSDK'

[ -x "$WINE" ] || { echo "Wine not found at $WINE"; exit 1; }

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# /Users/max/... -> Z:\Users\max\...   (Wine maps Z: to /)
WIN_ROOT="Z:$(printf '%s' "$ROOT" | tr '/' '\\')"

# Wine's own chatter, not the build's.
NOISE='mvk-info|VK_|pipelineCache|model:|type:|vendorID|deviceID|memory|GPU |Metal|Family|Tier|supports|winediag'

cd "$ROOT"
set -o pipefail
"$WINE" "$PYTHON" -c "import sys; sys.path.insert(0, r'${WIN_ROOT}\\tools'); from build.cli import main; sys.exit(main())" \
    --toolkit-dir "$TOOLKIT" --winsdk-dir "$WINSDK" "$@" 2>&1 | grep -viE "$NOISE" || exit $?
