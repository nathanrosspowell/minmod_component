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
            return 0xaccf8b33; // CRC32 of "test".
        }
        static std::string GetStaticName()
        {
            return "test";
        }

    public:
        // component::Interface.
        virtual component::Interface::IdPair GetId() const override
        {
            return std::make_pair(GetStaticId(), GetStaticName());
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
        static component::Registrant<TestComponent> ms_registrant;

    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;
    };
}
