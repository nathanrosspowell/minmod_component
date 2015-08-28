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
            using Func = std::function<UniquePtr(const Id, const Name)>;
            explicit ScopedRegistrant(const Id id, const Name& name, Func func);
            ~ScopedRegistrant();

        private:
            const Id m_id;
            const Name m_name;
        };
    }
}
