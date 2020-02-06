#!/bin/bash

error() {
  echo "$1" >&2
  echo "Please run this from the main folder." >&2
  exit 1
}

git submodule update --init --recursive
cd godot-cpp/ || error "No such file or directory: godot-cpp/"
scons platform=linux generate_bindings=yes use_custom_api_file=yes custom_api_file=../api.json || error "Scons not found. Please install scons."
cp bin/godot-cpp.linux.64.a ../libgodot-linux64.a