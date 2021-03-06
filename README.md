# `minmod_component`

[![Build Status](https://travis-ci.org/nathanrosspowell/minmod_component.svg?branch=master)](https://travis-ci.org/nathanrosspowell/minmod_component)
[![Build status](https://ci.appveyor.com/api/projects/status/afjoqbyjhehqqw5s?svg=true)](https://ci.appveyor.com/project/nathanrosspowell/minmod-component)
[![Project Stats](https://www.openhub.net/p/minmod_component/widgets/project_thin_badge.gif)](https://www.openhub.net/p/minmod_component)

A minimal modern C++ component system.
- Minimal: What I decided as the basic needs for the system and nothing more
- Modern: Using features from C++11/14/17 when it makes sense, not just for the sake of it.

# Design choices

* New components are easy to code
  - Derive from an interface and implement the methods
  - No 'auto generated code' e.g. functions and types hidden away in macros
  - No files with lists of registration code
* Components are easy to instantiate
* All components can be deserialized and serialized
* Components are not tied to an 'entity' model e.g. a manager could have components


# Guide

### Making a new component class
1. Make a new class or take an existing one
2. Inherit from `Component::Interface`
3. Override the abstract virtual functions

### Registering a new component
* Staticly registered:
  - Implement the static functions `GetStaticId()` and `GetStaticName()`
  - Add a static `Registrant` instance to your class
* Default Registered inside of a scope:
  - Create a `Registrant` inside of your scope
      * e.g. having a mission component registered in the factory only when inside of a mission scope
  - or, call the functions `Component::Factory::GetInstance().Insert<MyClass>()` and `Component::Factory::::GetInstance().Erase<MyClass>()`
* Custom registration:
  - The factory takes an id, and name (needed for JSON serialization) and a 'create' lambda
  - You can register a custom version of an existing component with new versions of these
  - eg:
```cpp
component::Id id = 10101; // Custom id.
std::string name = "hotrod"; // Custom name.
auto createFunction = [name]()
    {
        return std::make_unique<CarComponent>(name); // Uses a custom constructor.
    };
component::Factory::GetInstance().Insert(id, name, createFunction);
```

### Instanciating one (or many) components
* Insert a owner id and a `component::Manager::InsertList` into the `component::Manager`
  - `InsertList` is a list of pairs of `component::Id` and `json11::Json::object`
* Insert a owner id and path to a JSON object
  - The JSON file needs a `"components"` element which is a list of pairs of `string` to `'object`.
  - e.g. [cool.json](data/cool.json)

# Dependencies

* [json11](https://github.com/dropbox/json11) by [Dropbox](https://github.com/dropbox/) (already bundled with the source)


# To Do

### Split up test code

The test code should be in a seperate folder from `src`.

### With test code split away, build _real_ source as a library

Builds the code as a library and link against it.

### Build against `GCC`

The current `makefile` only uses `clang`.

### Add Ready and Not Ready callbacks

The linking of the components needs to have a final function call to set 'is ready' on components that need to wait for others to be present.

### Make allocation of components come from the registration classes

Figure out how to make strongly typed memory pools for each component type. These should live in the registration classes. That would allow for non-component framework update loops to be added via the registration class.
