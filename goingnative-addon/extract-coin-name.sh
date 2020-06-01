#!/usr/bin/env bash

set -euo pipefail

command -v git >/dev/null 2>&1 || (echo "Please install git" && exit 1)

branch_name="$(git rev-parse --abbrev-ref HEAD)"

echo "${branch_name#*-}" # remove prefix ending in "-"
