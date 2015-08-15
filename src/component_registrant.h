#pragma once
// minmod
#include "component_factory.h"
// Debug
#include <iostream> 

namespace minmod
{
    namespace component
    {
        template< class COMPONENT >
        class Registrant
        {
        public:
            Registrant()
            {
                TRACE("Insert component: "<<COMPONENT::GetStaticName());
                Factory::GetInstance().Insert<COMPONENT>();
            }

            ~Registrant()
            {
                TRACE("Erase component: "<<COMPONENT::GetStaticName());
                Factory::GetInstance().Erase<COMPONENT>();
            }
        };
    }
}
