// stl
#include <iostream>
#include <string>
#include <fstream>
// minmod
#include "component_types.h"
#include "component_manager.h"
#include "component_handle.h"
#include "component_static_registrant.h"
#include "component_scoped_registrant.h"
#include "custom_component.h"
#include "linking_component.h"
#include "test_component.h"
#include "json11.hpp"
// Debug
#include <iostream>

int main()
{
    // Using statements just for the main scope block.
    using namespace minmod;
    using namespace minmod::component;
    using namespace json11;
    TRACE("Start main()"); // There will be some logs from static constructors before this line.
    TRACE("Create Component::Manager");
    Manager cm;
    OwnerId bob = 808; // Hook into id generator.
    OwnerId sam = 543; // Hook into id generator.
    // Pairs of id to json object.
    Manager::InsertList bobsComponentMap = {// clang-format off
        {
            TestComponent::GetStaticId(),
            Json::object{
                { "x", 102 },
                { "z", 15 }
            }
        },
        {
            LinkingComponent::GetStaticId(),
            Json::object{}
        }
    }; // clang-format on
    TRACE("Add bob");
    cm.Insert(bob, bobsComponentMap); // Insert list of componentMap.
    TRACE("Get bobs TestComponent");
    auto bobsTest = cm.Get<TestComponent>(bob);
    UNUSED(bobsTest);
    assert(bobsTest != nullptr);
    TRACE("Got: " << bobsTest->GetName());
    TRACE("Get bobs LinkingComponent");
    auto bobsLink = cm.Get(bob, "link");
    UNUSED(bobsLink);
    assert(bobsLink != nullptr);
    TRACE("Got: " << bobsLink->GetName());
    TRACE("Get bobs TestComponent via handle");
    Handle<TestComponent> testHandle(cm, bob, TestComponent::GetStaticId());
    if (Handle<TestComponent>::Adapter test = testHandle.Get())
    {
        UNUSED(test);
        TRACE("Got: " << test->GetName());
    }
    TRACE("Get bobs LinkingComponent via handle");
    Handle<LinkingComponent> linkHandle(cm, bob);
    if (auto link = linkHandle.Get())
    {
        auto& linkRef = link.Get();
        UNUSED(linkRef);
        TRACE("Got: " << linkRef.GetName());
    }
    linkHandle.Do([](auto& linkRef)
                  {
                      UNUSED(linkRef);
                      TRACE("Handle::Do Got: " << linkRef.GetName());
                  });
    TRACE("Add sam");
    cm.Insert(sam, "../data/cool.json"); // Create from json file.
    TRACE("Get sams TestComponent");
    auto samsTest = cm.Get(sam, TestComponent::GetStaticId());
    UNUSED(samsTest);
    assert(samsTest != nullptr);
    TRACE("Got: " << samsTest->GetName());
    Json cmJson = cm.Serialize();
    TRACE("Dump Manager" << cmJson.dump());
    Manager::EraseList samsComponentMap = {
        LinkingComponent::GetStaticId() // Erase by number.
    };
    TRACE("Remove sams LinkingComponent");
    cm.Erase(sam, samsComponentMap); // Erase list of componentMap.
    TRACE("Try and get sams Link");
    auto samsLink = cm.Get(sam, LinkingComponent::GetStaticId());
    assert(samsLink == nullptr);
    Name name = samsLink ? samsLink->GetName() : Name("nullptr");
    TRACE("Got: " << name);
    TRACE("Remove bob");
    cm.Erase(bob);
    TRACE("Clone Manager");
    Manager cloneManager;
    cloneManager.Deserialize(cmJson);
    TRACE("Dump Clone Manager" << cloneManager.Serialize().dump());
    TRACE("Custom types test, open scope");
    {
        Id ohFive = 2005;
        Id ohNine = 2009;
        ScopedRegistrant custom1(ohFive, "oh-five", [](auto id, auto name)
                                 {
                                     return std::make_unique<CustomComponent>(id, name, 5);
                                 });
        ScopedRegistrant custom2(ohNine, "oh-nine", [](auto id, auto name)
                                 {
                                     return std::make_unique<CustomComponent>(id, name, 9);
                                 });

        OwnerId ned = 232;
        Manager::InsertList nedsComponents = {{ohFive, Json::object{{"size", 3}}}, {ohNine, Json::object{{"size", 9}}}};
        Manager nedsManager;
        nedsManager.Insert(ned, nedsComponents);
    }
    TRACE("Custom types test, close scope");
    TRACE("End main()");
    return 0;
}
