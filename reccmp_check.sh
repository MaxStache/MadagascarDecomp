#!/bin/bash
# macOS equivalent of reccmp_check.bat: build with the VC++ Toolkit 2003 under
# Wine, then compare the result against the original Game.exe with reccmp.
#
#   ./reccmp_check.sh                  # build + full report -> report.html
#   ./reccmp_check.sh 0x464ef0        # verbose asm diff for one address
#   ./reccmp_check.sh --vtable         # also check vtables
#   ./reccmp_check.sh --no-build       # skip the build, just compare
#
# One-time setup, if reccmp-user.yml is missing:
#   put the original Game.exe in ./originals/   (sha256 a8dcfe45...)
#   ./.venv/bin/reccmp-project detect --search-path ./originals
set -e

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

BUILD_DIR="$ROOT/src/console/game_framework/win32/bin/Win32 D3D Release"
VENV="$ROOT/.venv"
TOTAL=8244

# reccmp runs cvdump.exe through Wine to read the PDB.
export PATH="$HOME/Applications/Wine Staging.app/Contents/Resources/wine/bin:$PATH"
export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-vs2003}"
export WINEDEBUG="${WINEDEBUG:--all}"

VERBOSE=""
VTABLE=0
DOBUILD=1
for a in "$@"; do
    case "$a" in
        --vtable)   VTABLE=1 ;;
        --no-build) DOBUILD=0 ;;
        *)          VERBOSE="$a" ;;
    esac
done

[ -d "$VENV" ] || { echo "No .venv. Run: python3 -m venv .venv && ./.venv/bin/pip install reccmp"; exit 1; }
[ -f "$ROOT/reccmp-user.yml" ] || { echo "No reccmp-user.yml - see setup note at the top of this script."; exit 1; }

if [ "$DOBUILD" = "1" ]; then
    echo "BUILDING..."
    "$ROOT/build-wine.sh" --pdb --keep-unused \
        --define DECOMP_ENABLE_CONSOLE --define DECOMP_DEBUG_WINDOWED \
        || { echo "BUILD FAILED - skipping reccmp."; exit 1; }
fi

cd "$BUILD_DIR"
echo "CHECKING..."
if [ -z "$VERBOSE" ]; then
    "$VENV/bin/reccmp-reccmp" --target GAME --total "$TOTAL" --nolib --html "$ROOT/report.html"
else
    "$VENV/bin/reccmp-reccmp" --target GAME --verbose "$VERBOSE"
fi

if [ "$VTABLE" = "1" ]; then
    echo "CHECKING VTABLES..."
    "$VENV/bin/reccmp-vtable" --target GAME
fi
