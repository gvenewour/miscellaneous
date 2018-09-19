#!/bin/bash

rm -rf build
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --build build --target test
cmake --build build --target package
