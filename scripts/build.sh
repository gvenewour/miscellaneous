#!/bin/bash

rm -rf build
cmake -H. -Bbuild
cmake --build build
cmake --build build --target test
cmake --build build --target package
