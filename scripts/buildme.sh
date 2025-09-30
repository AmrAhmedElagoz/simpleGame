#!/bin/bash
cd "$(dirname "$0")/.."
rm -rf build
mkdir build
cd build

if [ "$1" == "externals" ]; then
    echo "Building with externals (rebuild SFML & ImGui-SFML)..."
    cmake -DBUILD_EXTERNALS=ON ..
else
    echo "Building with prebuilt SFML & ImGui-SFML..."
    cmake -DBUILD_EXTERNALS=OFF ..
fi

cmake --build .
