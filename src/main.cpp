// stl
#include <iostream>
#include <string>
#include <fstream>
// minmod
#include "component_manager.h"
#include "test_component.h"
#include "json11.hpp"

int main()
{
    // Using statements just for the main scope block.
    using namespace minmod;
    using namespace minmod::Component;
    // Component Manager.
    Manager cm;
    OwnerId bobby = 42; // Hook into id generator.
    OwnerId sam = 44; // Hook into id generator.
    // Bobs stuff.
    Manager::InsertComponents bobsComponents = {
        {
            TestComponent::GetStaticId(), // Create from id.
            json11::Json::object{ { "x",  102 }, { "z", 15 } } // Create JSON data to be deserialised.
        }
    };
    cm.Insert( bobby, bobsComponents ); // Insert list of components.
    // Sams stuff. 
    cm.Insert( sam, "../data/cool.json" ); // Create from strings.
    Manager::EraseComponents samsComponents = {
        { TestComponent::GetStaticId() } // Erase by number.
    };
    cm.Erase( sam, samsComponents ); // Erase list of components.
    return 0;
}
