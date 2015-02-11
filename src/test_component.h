#ifndef MINMOD_COMPONENT__TEST_COMPONENT
#define MINMOD_COMPONENT__TEST_COMPONENT
#pragma once

#include "component_interface.h"

class TestComponent : public ComponentInterface
{
private:
    virtual void Create() override {}
    virtual void Load() override {}
    virtual void Ready() override {}
    virtual void Update() override {}
    virtual void Unload()  override {}
    virtual void Destroy()  override {}
};

#endif 
