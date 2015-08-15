// stl
#include <iostream>
#include <string>
#include <fstream>
// minmod
#include "component_manager.h"
#include "test_component.h"
#include "linking_component.h"
#include "json11.hpp"
// Debug
#include <iostream> 

int main()
{
    TRACE("Start main()");
    // Using statements just for the main scope block.
    using namespace minmod;
    using namespace minmod::component;
    // Component Manager.
    TRACE("Create Component::Manager");
    Manager cm;
    OwnerId bobby = 42; // Hook into id generator.
    OwnerId sam = 44; // Hook into id generator.
    // Bobs stuff.
    TRACE("Add bobby");
    Manager::InsertList bobsComponentMap = {
        {
            TestComponent::GetStaticId(), // Create from id.
            json11::Json::object{ { "x",  102 }, { "z", 15 } } // Create JSON data to be deserialised.
        },
        {
            LinkingComponent::GetStaticId(), // Create from id.
            json11::Json::object{ } // Create JSON data to be deserialised.
        }
    };
    cm.Insert( bobby, bobsComponentMap ); // Insert list of componentMap.
    // Test components
    {
        auto component = cm.Get<TestComponent>(bobby);
        assert(component != nullptr);
        TRACE("Got component: "<<component->GetName());
    }
    {
        auto component = cm.Get(bobby, "link");
        assert(component != nullptr);
        TRACE("Got component: "<<component->GetName());
    }
    // Sams stuff. 
    TRACE("Add sam");
    cm.Insert( sam, "../data/cool.json" ); // Create from strings.
    Manager::EraseList samsComponentMap = {
        LinkingComponent::GetStaticId() // Erase by number.
    };
    {
        auto component = cm.Get(sam, TestComponent::GetStaticId());
        assert(component != nullptr);
        TRACE("Got component: "<<component->GetName());
    }
    // Test components
    cm.Erase( sam, samsComponentMap ); // Erase list of componentMap.
    {
        auto component = cm.Get(sam, LinkingComponent::GetStaticId());
        assert(component == nullptr);
        std::string name = component? component->GetName() : std::string("nullptr");
        TRACE("Got component: "<<name);
    }
    // Remove bobby.
    TRACE("Remove bobby");
    cm.Erase(bobby);
    TRACE("End main()");
    return 0;
}

