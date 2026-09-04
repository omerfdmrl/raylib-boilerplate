#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_DIR"

if ! command -v valgrind &> /dev/null; then
    echo "valgrind not installed, skipping memory check"
    exit 0
fi

echo "Building test binary..."
make test 2>&1 | head -5

echo ""
echo "Running valgrind on test binary..."
valgrind --leak-check=full --error-exitcode=1 --track-origins=yes \
    --suppressions=valgrind.suppress \
    ./build/results/bin

echo ""
echo "Valgrind: No memory errors detected."
