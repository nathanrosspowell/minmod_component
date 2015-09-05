#pragma once
#include "component_interface.h"
#include "component_static_registrant.h"
#include "json11.hpp"

namespace test
{
    namespace mmc = minmod::component;

    class CustomComponent : public mmc::Interface
    {
    public:
        CustomComponent(const mmc::Id id, const mmc::Name& name, const std::int32_t max);
        virtual ~CustomComponent() = default;

        void Print();

    public:
        // mmc::Interface.
        virtual mmc::Id GetId() const
        {
            return m_id;
        }
        virtual mmc::Name GetName() const
        {
            return m_name;
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
        const mmc::Id m_id;
        const mmc::Name m_name;
        std::int32_t m_max;
        std::int32_t m_size;
    };
}
