#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace minmod
{
    class TestComponent;
    class LinkingComponent : public component::Interface
    {
    public:
        // component::Factory Registration.
        static component::Id GetStaticId()
        {
            return 0xd8f2a84d; // CRC32 of "link"
        }
        static std::string GetStaticName()
        {
            return "link";
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
        virtual void Deserialize(json11::Json /*json*/) override
        {
        }
        virtual json11::Json Serialize() const override
        {
            return json11::Json::object{};
        }
        virtual void MakeLinks(component::Linker& liner) override;
        virtual void Create() override
        {
        }
        virtual void Destroy() override
        {
        }

    private:
        static component::StaticRegistrant<LinkingComponent> ms_StaticRegistrant;

    private:
        TestComponent* m_test;
    };
}
