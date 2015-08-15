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
    // Using statements just for the main scope block.
    using namespace minmod;
    using namespace minmod::component;
    TRACE("Start main()"); // There will be some logs from static constructors before this line.
    TRACE("Create Component::Manager");
    Manager cm;
    OwnerId bob = 808; // Hook into id generator.
    OwnerId sam = 543; // Hook into id generator.
    Manager::InsertList bobsComponentMap = { // Create stuff for bob.
        {
            TestComponent::GetStaticId(), // Create from id.
            json11::Json::object{ { "x",  102 }, { "z", 15 } } // Create JSON data to be deserialised.
        },
        {
            LinkingComponent::GetStaticId(), // Create from id.
            json11::Json::object{ } // Create JSON data to be deserialised.
        }
    };
    TRACE("Add bob");
    cm.Insert( bob, bobsComponentMap ); // Insert list of componentMap.
    TRACE("Get bobs TestComponent");
    auto bobsTest = cm.Get<TestComponent>(bob);
    assert(bobsTest != nullptr);
    TRACE("Got: "<<bobsTest->GetName());
    TRACE("Get bobs LinkingComponent");
    auto bobsLink = cm.Get(bob, "link");
    assert(bobsLink != nullptr);
    TRACE("Got: "<<bobsLink->GetName());
    TRACE("Add sam");
    cm.Insert( sam, "../data/cool.json" ); // Create from json file.
    TRACE("Get sams TestComponent");
    auto samsTest = cm.Get(sam, TestComponent::GetStaticId());
    assert(samsTest != nullptr);
    TRACE("Got: "<<samsTest->GetName());
    Manager::EraseList samsComponentMap = {
        LinkingComponent::GetStaticId() // Erase by number.
    };
    TRACE("Remove sams LinkingComponent");
    cm.Erase( sam, samsComponentMap ); // Erase list of componentMap.
    TRACE("Try and get sams Link");
    auto samsLink = cm.Get(sam, LinkingComponent::GetStaticId());
    assert(samsLink == nullptr);
    std::string name = samsLink? samsLink->GetName() : std::string("nullptr");
    TRACE("Got: "<<name);
    TRACE("Remove bob");
    cm.Erase(bob);
    TRACE("End main()");
    return 0;
}

