"""Builds the Win32 game. Usage: python tools/build.py ["D3D Debug"] [options]; see --help."""

import sys

from build.cli import main

sys.exit(main())
