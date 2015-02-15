#ifndef MINMOD_COMPONENT__TEST_COMPONENT
#define MINMOD_COMPONENT__TEST_COMPONENT
#pragma once

#include "component_interface.h"
#include "component_registrant.h"
#include "json11.hpp"

namespace minmod
{
    class TestComponent : public ComponentInterface
    {
    public:
        static Component::Id GetStaticId() { return reinterpret_cast<Component::Id>(&ms_id);  }
        static std::string GetStaticName() { return "test"; }

    private:
        virtual Component::Id GetId() const { return GetStaticId(); }
        virtual std::string GetName() const { return GetStaticName(); }
        virtual void Deserialize(json11::Json json) override;
        virtual json11::Json Serialize() const override;
        virtual void Create() override {}
        virtual void Destroy()  override {}

    private: 
        static const bool ms_id;
        static ComponentRegistrant<TestComponent> ms_registrant;

    private:
        int x = 0;
        int y = 0;
        int z = 0;
    };
}
#endif 
