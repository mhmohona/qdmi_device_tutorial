# Copyright (c) 2024 - 2025 Munich Quantum Software Stack Project
# All rights reserved.
#
# Licensed under the Apache License v2.0 with LLVM Exceptions (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE.md
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

"""Command line interface for the tutorial QDMI device library."""

import argparse
import sys
from functools import partial

from . import tutorial_QDMI_CMAKE_DIR, tutorial_QDMI_INCLUDE_DIR, tutorial_QDMI_LIBRARY_PATH, __version__


def main() -> None:
    """Entry point for the tutorial-qdmi command line interface.

    This function is called when running the `tutorial-qdmi` script.

    .. code-block:: bash

        tutorial-qdmi [--version] [--include_dir] [--cmake_dir] [--lib_path]

    It provides the following command line options:

    - :code:`--version`: Print the version and exit.
    - :code:`--include_dir`: Print the path to the tutorial-qdmi C/C++ include directory.
    - :code:`--cmake_dir`: Print the path to the tutorial-qdmi CMake module directory.
    - :code:`--lib_path`: Print the path to the tutorial-qdmi shared library.
    """
    make_parser = partial(
        argparse.ArgumentParser, prog="tutorial-qdmi", description="Command line interface for the tutorial QDMI device library."
    )
    if sys.version_info >= (3, 14):
        make_parser = partial(make_parser, suggest_on_error=True)

    parser = make_parser()
    parser.add_argument(
        "--version",
        action="version",
        version=f"{__version__}",
    )
    parser.add_argument(
        "--include_dir",
        action="store_true",
        help="Print the path to the tutorial-qdmi C/C++ include directory",
    )
    parser.add_argument(
        "--cmake_dir",
        action="store_true",
        help="Print the path to the tutorial-qdmi CMake module directory",
    )
    parser.add_argument(
        "--lib_path",
        action="store_true",
        help="Print the path to the tutorial-qdmi shared library",
    )

    args = parser.parse_args()

    if args.include_dir:
        print(tutorial_QDMI_INCLUDE_DIR)
    elif args.cmake_dir:
        print(tutorial_QDMI_CMAKE_DIR)
    elif args.lib_path:
        print(tutorial_QDMI_LIBRARY_PATH)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
