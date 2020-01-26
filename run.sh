#!/bin/bash
set -euo pipefail

cd $(dirname $(readlink -f $0))

if [[ $# -ne 2 ]]; then
  echo "Usage: $0 <language> <problem_number>"
  echo "  language: 'rust', 'cpp', or 'golang'"
  exit 2
fi

if [[ "$1" != "golang" ]] && [[ "$1" != "rust" ]] && [[ "$1" != "cpp" ]]; then
  echo "language options are golang, cpp, or rust"
  exit 2
fi

make -C $1 PROBLEM=$2
