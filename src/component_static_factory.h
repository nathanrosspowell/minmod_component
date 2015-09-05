#pragma once
//- minmod.
#include "component_factory.h"

namespace minmod
{
    namespace component
    {
        /* A StaticFactory for components.
         *
         * Easy access to one static factory.
         * This can be used to register components from anywhere in the game.
         * A manager still needs to have this factory passed into it.
         */
        class StaticFactory
        {
        public: //-Singleton code.

            /* Singleton interface
             *
             * To allow static registration before the <main> function runs, 
             * there is a static getter function.
             *
             * @return a refference to the <StaticFactory> singleton
             */
            static Factory& GetInstance()
            {
                static Factory instance;
                return instance;
            }

        public: //- Public functions.

            /* Default constructor.
             *
             * Needed to allow the singleton interface.
             */
            StaticFactory() = default;

            /* Copy constructor.
             *
             * Explicitly deleted to stop duplicate <StaticFactory> instances.
             */
            StaticFactory(StaticFactory const&) = delete;

            /* Assignment operator.
             *
             * Explicitly deleted to stop duplicate <StaticFactory> instances.
             */
            void operator=(StaticFactory const&) = delete;
        };
    }
}
