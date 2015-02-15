#include "test_component.h"

namespace minmod
{
    const bool TestComponent::ms_id = true;
    ComponentRegistrant<TestComponent> TestComponent::ms_registrant;

    void TestComponent::Deserialize(json11::Json json)
    {
        x = json["x"].int_value();
        y = json["y"].int_value();
        z = json["z"].int_value();
    }

    json11::Json TestComponent::Serialize() const
    {
        return json11::Json::object {
            { "x", x },
            { "y", y },
            { "z", z }
        };
    }
}
