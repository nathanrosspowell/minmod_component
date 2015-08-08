#pragma once
#include "component_interface.h"
#include "component_registrant.h"
#include "json11.hpp"

namespace minmod
{
    class TestComponent : public Component::Interface
    {
    public:
        // Component::Factory Registration.
        static Component::Id GetStaticId() { return reinterpret_cast<Component::Id>(&ms_id); }
        static std::string GetStaticName() { return "test"; }

    private:
        // Component::Interface.
        virtual Component::Id GetId() const { return GetStaticId(); }
        virtual std::string GetName() const { return GetStaticName(); }
        virtual void Deserialize(json11::Json json) override;
        virtual json11::Json Serialize() const override;
        virtual void MakeLinks(Component::Linker& /*liner*/) override {}
        virtual void Create() override {}
        virtual void Destroy()  override {}

    private: 
        static const bool ms_id; // Address of this variable as a cheap unique id per class.
        static Component::Registrant<TestComponent> ms_registrant;

    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;
    };
}
