#pragma once
// minmod
#include "component_static_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        /* Helper class for statically registering a class in the <Factory>.
         *
         * The template class needs to inherit from <Interface> and also implement:
         *     1) <GetStaticId> for the <Id>
         *     2) <GetStaticName> for the <Name>
         */
        template <class COMPONENT> class StaticRegistrant
        {
        public:
            /* Constructor.
             *
             * Auto adds the component to the factory using the template information.
             */
            StaticRegistrant()
            {
                TRACE("Insert component: " << COMPONENT::GetStaticName());
                StaticFactory::GetInstance().Insert<COMPONENT>();
            }

            /* Destructor.
             *
             * Auto removes the component to the factory using the template information.
             */
            ~StaticRegistrant()
            {
                TRACE("Erase component: " << COMPONENT::GetStaticName());
                StaticFactory::GetInstance().Erase<COMPONENT>();
            }
        };
    }
}
