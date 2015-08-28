#include "custom_component.h"
// minmod
#include "component_linker.h"
// Debug
#include <iostream>

namespace minmod
{
    CustomComponent::CustomComponent(const component::Id id, const component::Name& name, const std::int32_t max) : m_id(id), m_name(name), m_max(max), m_size(0)
    {
    }

    void CustomComponent::Print()
    {
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
