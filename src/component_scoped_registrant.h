#pragma once
// minmod
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        class Factory;

        /* Helper class for registering a class in the <Factory>.
         *
         * When a component variation wants to be registered to the <Factory>.
         * It is not tied to any static helper functions, 
         * so specialist variations of existing components can be indapendantly.
         *
         * The created component from <ScopedRegistrant::Func> has to do this:
         *     1) <Interface::GetId> matches <Id> passed to <ScopedRegistrant>
         *     2) <Interface::GetName> matches <Name> passed to <ScopedRegistrant>
         */
        class ScopedRegistrant
        {
        public: //- Public types.

            /* Function to create the <UniquePtr> for the component.
             *
             * This passes all of the parameters from the constructor to the create functions.
             * The <Id> and <Name> of have to be pushed into the component somehow,
             * (if they are not already in static helper functions).
             */
            using Func = std::function<UniquePtr(const Id, const Name)>;

        public: //- Public functions.

            /* Constructor.
             * @factory the <Factory> used for registering.
             * @id the <Id> for the registration.
             * @name the <Name> for the registration.
             * @func the <Func> for the registration.
             *
             * Inserts the component variation into the static <Factory>.
             */
            ScopedRegistrant(Factory& factory, const Id id, const Name& name, Func func);

            /* Destructor.
             *
             * Erases the component variation from the static <Factory>.
             */
            ~ScopedRegistrant();

        private: //- Private members.

            // The <Factory> to use for registration.
            Factory& m_factory;

            // The <Id> of the registration.
            const Id m_id;

            // The <Name> of the registration.
            const Name m_name;
        };
    }
}
