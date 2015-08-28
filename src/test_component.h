#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
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
            return 0xaccf8b33; // CRC32 of "test".
        }
        static component::Name GetStaticName()
        {
            return "test";
        }

    public:
        // component::Interface.
        virtual component::Id GetId() const
        {
            return GetStaticId();
        }
        virtual component::Name GetName() const
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
        static component::StaticRegistrant<TestComponent> ms_StaticRegistrant;

    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;
    };
}
