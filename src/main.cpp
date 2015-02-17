#include <iostream>
#include <string>
#include <fstream>

#include "component_manager.h"
#include "test_component.h"
#include "json11.hpp"

int main(int argc, char* argv[])
{
    using namespace minmod;

    // Suppress warnings.
    (void)argc; (void)argv;

    // Bobs stuff.
    OwnerId bobby = 42; // Hook into id generator.
    ComponentManager::AddComponents bobsComponents = {
        { TestComponent::GetStaticId(), json11::Json::object{ { "x",  99 }, { "z", 101 } } }
    };

    // Sam.
    OwnerId sam = 44; // Hook into id generator.

    // Component Manager.
    ComponentManager cm;
    cm.Add( bobby, bobsComponents );
    cm.Add( sam, "../data/cool.json" );
    ComponentManager::RemoveComponents samsComponents = {
        { TestComponent::GetStaticId() } 
    };
    cm.Remove( sam, samsComponents );

    return 0;
}
