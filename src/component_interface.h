#pragma once
#ifndef MINMOD_COMPONENT__COMPONENT_INTERFACE
#define MINMOD_COMPONENT__COMPONENT_INTERFACE

#include <cstdint>
#include <string>
#include "json11.hpp"

class ComponentInterface
{
  public:
    using Id = std::size_t;

  public:
    // It work with the interface, each component mush have the following static function:
    // static ComponentInterface::Id GetStaticId() = 0;
    // static std::string GetStaticName() = 0;

  private:
    virtual Id GetId() const = 0;
    virtual std::string GetName() const = 0;
    virtual void Create() = 0;
    virtual void Load(json11::Json json) = 0;
    virtual void Ready() = 0;
    virtual void Update() = 0;
    virtual void Unload() = 0;
    virtual void Destroy() = 0;
};

#endif 
