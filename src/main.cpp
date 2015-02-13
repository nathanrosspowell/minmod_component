#include <iostream>

#include "component_manager.h"
#include "test_component.h"

int main(int argc, char* argv[])
{
    // Suppress warnings.
    (void)argc; (void)argv;

    // Test print.
    auto add = [](auto x, auto y) {return x + y;};
    std::cout << "Hello World! From C++ " << add( 8, 6 ) << std::endl;

    // Bobs stuff.
    ComponentManager::OwnerId bobby = 42;
    std::shared_ptr<ComponentInterface> testPtr;
    testPtr.reset(new TestComponent());
    ComponentManager::ComponentMap bobsComponents = {
        { 0, testPtr }
    };

    // Component Manager.
    ComponentManager cm;
    cm.Add( bobby, bobsComponents );

    return 0;
}
