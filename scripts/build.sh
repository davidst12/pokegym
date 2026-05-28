#!/usr/bin/env bash

set -e

BUILD_DIR="build"

cmake -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug

cmake --build "$BUILD_DIR"
