#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    class TestComponent;
    class LinkingComponent : public mmc::Interface
    {
    public:
        // mmc::Factory Registration.
        static mmc::Id GetStaticId()
        {
            return 0xd8f2a84d; // CRC32 of "link"
        }
        static mmc::Name GetStaticName()
        {
            return "link";
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
        virtual void Deserialize(const json11::Json& /*json*/) override
        {
        }
        virtual json11::Json Serialize() const override
        {
            return json11::Json::object{};
        }
        virtual void MakeLinks(mmc::Linker& liner) override;
        virtual void Create() override
        {
        }
        virtual void Destroy() override
        {
        }

    private:
        static mmc::StaticRegistrant<LinkingComponent> ms_StaticRegistrant;

    private:
        TestComponent* m_test;
    };
}
