#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    class TestComponent : public mmc::Interface
    {
    public:
        TestComponent();
        virtual ~TestComponent();

        void Print();

    public:
        // mmc::Factory Registration.
        static mmc::Id GetStaticId()
        {
            return 0xaccf8b33; // CRC32 of "test".
        }
        static mmc::Name GetStaticName()
        {
            return "test";
        }

    public:
        // mmc::Interface.
        virtual mmc::Id GetId() const
        {
            return GetStaticId();
        }
        virtual mmc::Name GetName() const
        {
            return GetStaticName();
        }

    private:
        // mmc::Interface.
        virtual void Deserialize(const json11::Json& json) override;
        virtual json11::Json Serialize() const override;
        virtual void MakeLinks(mmc::Linker& /*liner*/) override
        {
        }
        virtual void Create() override
        {
        }
        virtual void Destroy() override
        {
        }

    private:
        static mmc::StaticRegistrant<TestComponent> ms_StaticRegistrant;

    private:
        std::int32_t m_x = 0;
        std::int32_t m_y = 0;
        std::int32_t m_z = 0;
    };
}
