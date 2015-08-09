#include <cassert>
#include "linking_component.h"
#include "test_component.h"
#include "component_linker.h"

namespace minmod
{
    component::Registrant<LinkingComponent> LinkingComponent::ms_registrant;
    const bool LinkingComponent::ms_id = true; // Address of this variable as a cheap unique id per class.

    void LinkingComponent::Deserialize(json11::Json /*json*/)
    {
    }

    json11::Json LinkingComponent::Serialize() const
    {
        return json11::Json::object{};
    }

    void LinkingComponent::MakeLinks(component::Linker& linker)
    {
        linker.Link<TestComponent>(
			[this](auto ptr)
		    {
				m_test = ptr;
				assert(m_test != nullptr);
		    },
			[this]()
			{ 
				m_test = nullptr;
			}
		);
    }
}
