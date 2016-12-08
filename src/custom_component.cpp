#include "custom_component.h"
// Debug
#include <iostream>

namespace test
{
    namespace mmc = minmod::component;

    CustomComponent::CustomComponent(const mmc::Id id, const mmc::Name& name, const std::int32_t max)
        : m_id(id), m_name(name), m_max(max), m_size(0)
    {
    }

    void CustomComponent::Print()
    {
        UNUSED(m_max);
        TRACE("Size: " << m_size << " Max: " << m_max);
    }

    void CustomComponent::Deserialize(const json11::Json& json)
    {
        m_size = json["size"].int_value();
    }

    json11::Json CustomComponent::Serialize() const
    {
        return json11::Json::object{{"size", m_size}};
    }
}
