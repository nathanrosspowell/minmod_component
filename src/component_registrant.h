#ifndef MINMOD_COMPONENT__COMPONENT_REGISTRANT
#define MINMOD_COMPONENT__COMPONENT_REGISTRANT
#pragma once

#include "component_factory.h"

namespace minmod
{
    template< class COMPONENT >
    class ComponentRegistrant
    {
    public:
        ComponentRegistrant()
        {
            ComponentFactory::Insert<COMPONENT>();
        }

        ~ComponentRegistrant()
        {
            ComponentFactory::Erase<COMPONENT>();
        }
    };
}

#endif
