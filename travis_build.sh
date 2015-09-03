#!/bin/bash
# Debug build and run.
pushd src
make debug
./minmod_component
# Release build and run.
make
./minmod_component
popd
