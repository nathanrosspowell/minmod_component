#pragma once
#include "component_interface.h"
#include "component_registrant.h"
#include "json11.hpp"

namespace minmod
{
    class TestComponent : public component::Interface
    {
    public:
        TestComponent();
        virtual ~TestComponent();

        void Print();

    public:
        // component::Factory Registration.
        static component::Id GetStaticId()
        {
            return reinterpret_cast<component::Id>(&ms_id);
        }
        static std::string GetStaticName()
        {
            return "test";
        }

    public:
        // component::Interface.
        virtual component::Id GetId() const
        {
            return GetStaticId();
        }
        virtual std::string GetName() const
        {
            return GetStaticName();
        }

    private:
        // component::Interface.
        virtual void Deserialize(json11::Json json) override;
        virtual json11::Json Serialize() const override;
        virtual void MakeLinks(component::Linker& /*liner*/) override
        {
        }
        virtual void Create() override
        {
        }
        virtual void Destroy() override
        {
        }

    private:
        static const bool ms_id; // Address of this variable as a cheap unique id per class.
        static component::Registrant<TestComponent> ms_registrant;

    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;
    };
}
