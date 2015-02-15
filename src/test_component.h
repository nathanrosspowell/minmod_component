#ifndef MINMOD_COMPONENT__TEST_COMPONENT
#define MINMOD_COMPONENT__TEST_COMPONENT
#pragma once

#include "component_interface.h"
#include "component_registrant.h"
#include "json11.hpp"

class TestComponent : public ComponentInterface
{
  public:
    static ComponentInterface::Id GetStaticId() { return reinterpret_cast<ComponentInterface::Id>(&ms_id);  }
    static std::string GetStaticName() { return "test"; }

  private:
    virtual ComponentInterface::Id GetId() const { return GetStaticId(); }
    virtual std::string GetName() const { return GetStaticName(); }
    virtual void Create() override {}
    virtual void Load(json11::Json /*json*/) override {}
    virtual void Ready() override {}
    virtual void Update() override {}
    virtual void Unload()  override {}
    virtual void Destroy()  override {}

  private: 
    static const bool ms_id;
    static ComponentRegistrant<TestComponent> ms_registrant;

  private:
    int x = 0;
    int y = 0;
    int z = 0;
};
#endif 
