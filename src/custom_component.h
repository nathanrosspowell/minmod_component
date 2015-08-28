#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace minmod
{
    class CustomComponent : public component::Interface
    {
    public:
        CustomComponent(const component::Id id, const component::Name& name, const std::int32_t max);
        virtual ~CustomComponent() = default;

        void Print();

    public:
        // component::Interface.
        virtual component::Id GetId() const
        {
            return m_id;
        }
        virtual component::Name GetName() const
        {
            return m_name;
        }

    private:
        // component::Interface.
        virtual void Deserialize(const json11::Json& json) override;
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
        const component::Id m_id;
        const component::Name m_name;
        std::int32_t m_max;
        std::int32_t m_size;
    };
}
