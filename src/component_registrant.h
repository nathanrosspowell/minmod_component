#pragma once
// minmod
#include "component_factory.h"

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
                Factory::Insert<COMPONENT>();
            }

            ~Registrant()
            {
                Factory::Erase<COMPONENT>();
            }
        };
    }
}
