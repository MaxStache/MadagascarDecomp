"""Builds the Win32 game. Usage: python build.py ["D3D Debug"] [options]; see --help."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "tools"))

from build.cli import main  # noqa: E402

sys.exit(main())
