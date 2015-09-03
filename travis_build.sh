#!/bin/bash
# Debug build and run.
make debug || exit 1
./minmod_component || exit 1
# Release build and run.
make || exit 1
./minmod_component || exit 1
