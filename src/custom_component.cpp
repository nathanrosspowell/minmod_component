#include "custom_component.h"
// minmod
#include "component_linker.h"
// Debug
#include <iostream>

namespace minmod
{
    CustomComponent::CustomComponent(component::Id id, std::string name, std::int32_t max) : m_id(id), m_name(name), m_max(max), m_size(0)
    {
    }

    void CustomComponent::Print()
    {
        TRACE("Size: " << m_size << " Max: " << m_max);
    }

    void CustomComponent::Deserialize(json11::Json json)
    {
        m_size = json["size"].int_value();
    }

    json11::Json CustomComponent::Serialize() const
    {
        return json11::Json::object{{"size", m_size}};
    }
}
