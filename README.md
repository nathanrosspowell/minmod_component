# `minmod_component`

[![Build Status](https://travis-ci.org/nathanrosspowell/minmod_component.svg?branch=master)](https://travis-ci.org/nathanrosspowell/minmod_component)

A minimal modern C++ component system.
- Minimal: What I decided as the basic needs for the system and nothing more
- Modern: Using features from C++11/14/17 when it makes sense, not just for the sake of it.

# Design choices

* New components are easy to code
  - Derive from an interface and implement the methods
  - No 'auto gen code' e.g. functions and types hidden in macros
  - No need to remember to register in another file: If it compiles, it will work
* Components are easy to instantiate
* All components can be deserialized and serialized

# Guide

### Making a new component
1. Make a new class
2. Inherit from `Component::Interface`
3. Override the abstract virtual functions
4. Add the two static functions `GetStaticId` and `GetStaticName`

### Registering a new component
Two options:
* Always registered:
  - Add a static `Registrant` instance to your class
* Registered inside of a scope:
  - Create a `Registrant` inside of that scope
  - or, directy call the functions `Component::Factory::Insert<MyClass>()` and `Component::Factory::Erase<MyClass>()`
