#pragma once
// minmod
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        class ScopedRegistrant
        {
        public:
            using Func = std::function<UniquePtr(Id, std::string)>;
            ScopedRegistrant(Id id, std::string name, Func func);
            ~ScopedRegistrant();

        private:
            Id m_id;
            std::string m_name;
        };
    }
}
