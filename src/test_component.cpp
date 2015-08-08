#include "test_component.h"
#include "component_linker.h"

namespace minmod
{
    Component::Registrant<TestComponent> TestComponent::ms_registrant;
    const bool TestComponent::ms_id = true; // Address of this variable as a cheap unique id per class.

    void TestComponent::Deserialize(json11::Json json)
    {
        m_x = json["x"].int_value();
        m_y = json["y"].int_value();
        m_z = json["z"].int_value();
    }

    json11::Json TestComponent::Serialize() const
    {
        return json11::Json::object {
            { "x", m_x },
            { "y", m_y },
            { "z", m_z }
        };
    }
}
