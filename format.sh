#!/bin/sh

set -e

python3 -m venv venv
venv/bin/pip install -r requirements.txt

find src -not -path './venv/*' -type f \( -iname '*.c' -o -iname '*.h' \) -print0 \
    | xargs -0 venv/bin/clang-format -i
