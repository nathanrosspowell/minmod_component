#include <cassert>
#include "linking_component.h"
#include "test_component.h"
#include "component_linker.h"
// Debug
#include <iostream> 
using std::cout;
using std::endl;

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
        TRACE("Adding TestComponent");
        linker.Link<TestComponent>(
			[this](auto ptr)
		    {
                TRACE("Linking pointer for TestComponent");
				m_test = ptr;
				assert(m_test != nullptr);
                m_test->Print();
		    },
			[this]()
			{ 
                TRACE("UnLinking pointer for TestComponent");
				m_test = nullptr;
			}
		);
    }
}
