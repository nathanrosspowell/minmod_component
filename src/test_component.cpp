#include "test_component.h"

namespace minmod
{
    const bool TestComponent::ms_id = true;
    ComponentRegistrant<TestComponent> TestComponent::ms_registrant;

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
