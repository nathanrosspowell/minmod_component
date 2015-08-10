// stl
#include <cassert>
// minmod
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

    void LinkingComponent::MakeLinks(component::Linker& linker)
    {
        TRACE("Adding TestComponent");
        linker.Link<TestComponent>(
            [this](auto ptr)
            {
                TRACE("Linking pointer for TestComponent");
                assert(m_test == nullptr);
                assert(ptr != nullptr);
                m_test = ptr;
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
