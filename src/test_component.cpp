#include "test_component.h"
// minmod
#include "component_linker.h"
// Debug
#include <iostream>

namespace test
{
    namespace mmc = minmod::component;

    mmc::StaticRegistrant<TestComponent> TestComponent::ms_StaticRegistrant;

    TestComponent::TestComponent()
    {
        TRACE("Constructor: " << this);
    }

    TestComponent::~TestComponent()
    {
        TRACE("Destructor: " << this);
    }

    void TestComponent::Print()
    {
        TRACE("X:" << m_x << " Y:" << m_y << " Z:" << m_z);
    }

    void TestComponent::Deserialize(const json11::Json& json)
    {
        m_x = json["x"].int_value();
        m_y = json["y"].int_value();
        m_z = json["z"].int_value();
    }

    json11::Json TestComponent::Serialize() const
    {
        return json11::Json::object{{"x", m_x}, {"y", m_y}, {"z", m_z}};
    }
}
