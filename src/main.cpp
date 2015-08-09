// stl
#include <iostream>
#include <string>
#include <fstream>
// minmod
#include "component_manager.h"
#include "test_component.h"
#include "linking_component.h"
#include "json11.hpp"

int main()
{
    // Using statements just for the main scope block.
    using namespace minmod;
    using namespace minmod::component;
    // Component Manager.
    Manager cm;
    OwnerId bobby = 42; // Hook into id generator.
    OwnerId sam = 44; // Hook into id generator.
    // Bobs stuff.
    Manager::InsertList bobsComponentList = {
        {
            TestComponent::GetStaticId(), // Create from id.
            json11::Json::object{ { "x",  102 }, { "z", 15 } } // Create JSON data to be deserialised.
        },
        {
            LinkingComponent::GetStaticId(), // Create from id.
            json11::Json::object{ } // Create JSON data to be deserialised.
        }
    };
    cm.Insert( bobby, bobsComponentList ); // Insert list of componentList.
    // Sams stuff. 
    cm.Insert( sam, "../data/cool.json" ); // Create from strings.
    Manager::EraseList samsComponentList = {
        TestComponent::GetStaticId() // Erase by number.
    };
    cm.Erase( sam, samsComponentList ); // Erase list of componentList.
    return 0;
}
