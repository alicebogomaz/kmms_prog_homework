#!/bin/bash

set -e

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"
BUILD_FOLDER="build_linux_${BUILD_SUFFIX}"

mkdir -p "${BUILD_FOLDER}"
cd "${BUILD_FOLDER}"

cmake -G "${BUILD_TYPE}" ..
cmake --build . -j "$(nproc)"

./keyboard
