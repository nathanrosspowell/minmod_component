#include "test_component.h"

namespace minmod
{
    const bool TestComponent::ms_id = true;
    ComponentRegistrant<TestComponent> TestComponent::ms_registrant;
}
