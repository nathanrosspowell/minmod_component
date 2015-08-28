#pragma once
// minmod
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        template <class COMPONENT> class StaticRegistrant
        {
        public:
            StaticRegistrant()
            {
                TRACE("Insert component: " << COMPONENT::GetStaticName());
                Factory::GetInstance().Insert<COMPONENT>();
            }

            ~StaticRegistrant()
            {
                TRACE("Erase component: " << COMPONENT::GetStaticName());
                Factory::GetInstance().Erase<COMPONENT>();
            }
        };
    }
}
