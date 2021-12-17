#!/usr/bin/env bash
pip install conan
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
