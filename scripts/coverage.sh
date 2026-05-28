#!/usr/bin/env bash

set -e

BUILD_DIR="build"
COVERAGE_DIR="coverage"

rm -rf $BUILD_DIR
rm -rf $COVERAGE_DIR

mkdir -p $BUILD_DIR
mkdir -p $COVERAGE_DIR

cmake -B $BUILD_DIR \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DENABLE_COVERAGE=ON

cmake --build $BUILD_DIR

ctest --test-dir $BUILD_DIR --output-on-failure

gcovr \
    --root . \
    --filter "game/" \
    --exclude ".*main.cpp" \
    --html-details $COVERAGE_DIR/coverage.html \
    --print-summary
