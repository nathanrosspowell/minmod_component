# `minmod_component`

[![Build Status](https://travis-ci.org/nathanrosspowell/minmod_component.svg?branch=master)](https://travis-ci.org/nathanrosspowell/minmod_component)

A minimal modern C++ component system.

# Design choices

* New components are easy to code
  - Derive from an interface and implement the methods
  - Minimal 'auto gen code' e.g. functions and types hidden in macros
  - No need to remember to register in another file: If it compiles, it will work
* Components are easy to instantiate
* All components can be deserialized and serialized
