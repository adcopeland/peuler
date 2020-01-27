#!/bin/bash
set -euo pipefail

cd $(dirname $(readlink -f $0))

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <language>"
  echo "  language: 'rust', 'cpp', or 'golang'"
  exit 2
fi

if [[ "$1" == "rust" ]]; then
  ls rust/peuler/src/bin/p[0-9]*.rs | xargs -n1 basename | sed 's/.rs$//' | sed 's/^p//' | sort -n
fi

if [[ "$1" == "cpp" ]]; then
  ls -ld cpp/src/p[0-9]* | awk '{print $9}' | xargs -n1 basename | sed 's/^p//' | sort -n
fi

if [[ "$1" == "golang" ]]; then
  ls -ld golang/src/p[0-9]* | awk '{print $9}' | xargs -n1 basename | sed 's/^p//' | sort -n
fi
