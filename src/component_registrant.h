#pragma once
#include "component_factory.h"

namespace minmod
{
    namespace Component
    {
        template< class COMPONENT >
        class Registrant
        {
        public:
            Registrant()
            {
                Factory::Insert<COMPONENT>();
            }

            ~Registrant()
            {
                Factory::Erase<COMPONENT>();
            }
        };
    }
}
