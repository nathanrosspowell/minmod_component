#pragma once
//- std.
#include <cstdint>
//- minmod.
#include "component_types.h"
#include "component_manager.h"
//- Debug.
#include <iostream>
#include <functional>

namespace minmod
{
    namespace component
    {
        class Manager;

        /* Templated component handle.
         *
         * Storing raw pointers to components that can be deleted at any time my the <Manager> is a bad idea.
         * The <Handle> wraps up the values needed to retrieve the pointer, then <Handle::Get> is used on demand.
         * The <Manager> is passed in, but if have a static manager, it would be easy to make a driving class set that automatically.
         */
        template <class T> class Handle
        {
        public: //- Public classes.

            /* Helper class for wrappinog raw pointers.
             *
             * This is a wrapper for the raw pointer which enforces a pointer check before accessing the value.
             * The explicit coversion to bool allows the pointer check to be done when you assign it inside of an `if` statement.
             */
            class Adapter
            {
            public: //- Public functions.


                /* If check operater.
                 *
                 * This provides a built in 'is valid' check.
                 * When an <Adapter> is set in an `if` statement, it will be checked. e.g.
                 *
                 *     if ( auto adapter = handle.Get())
                 *     {
                 *         // m_ptr must be true here.
                 *     }
                 */
                explicit operator bool() const;

                /* Derefference operator.
                 *
                 * It will assert if the <Adapter> validity hasn't been checked.
                 *
                 * @return component pointer.
                 */
                T* operator->();

                /* Const derefference operator.
                 *
                 * It will assert if the <Adapter> validity hasn't been checked.
                 *
                 * @return const component pointer.
                 */
                const T* operator->() const;
                
                /* Get a reference to the pointer.
                 *
                 * It will assert if the <Adapter> validity hasn't been checked.
                 *
                 * @return component refference.
                 */
                T& Get();

                /* Get a const reference to the pointer.
                 *
                 * It will assert if the <Adapter> validity hasn't been checked.
                 *
                 * @return const component refference.
                 */
                const T& Get() const;

            private: //- Private members.

                /* Constructor.
                 * @ptr the typed component pointer.
                 *
                 * These will always be created with a pointer, even if it's `nullptr`.
                 *
                 * Only <Handle::Get> class can access the private constructor.
                 */
                explicit Adapter(T* const ptr);
                friend Adapter Handle::Get() const;

            private: //- Private members.

                /* Unchangeable pointer to a copmonent.
                 *
                 * This can be `nullptr`.
                 */
                T* const m_ptr;

                /* Checked state.
                 *
                 * Defaults to false, set to true when <operator bool()> has been called.
                 */
                mutable bool m_checked;
            };

        public: //- Public functions.

            /* Constructor.
             * @manager the compoennt <Manager>.
             * @ownerId the owner of the component.
             * @id the component <Id>.
             *
             * Sets all the needed parameters.
             */
            Handle(Manager& manager, OwnerId ownerId, Id id);

            /* Constructor.
             * @manager the compoennt <Manager>.
             * @ownerId the owner of the component.
             *
             * This sets the <m_componentId> using a <GetStaticId> property on <T>.
             */
            Handle(Manager& manager, OwnerId ownerId);

            /* Getter for the pointer.
             *
             * The way to access the component pointer is through this function.
             * The returned <Adapter> should *NOT* be cached.
             *
             * @return <Adapter> wrapping the raw component pointer.
             */
            Adapter Get() const;

            /* Conditional execution of a function on the pointer.
             *
             * When a small function wants to be done on component pointers.
             * sometimes it's nice not to have to write if statements.
             * This function takes a lambda that takes a reference to the component,
             * it only executes if the component is currently valid.
             *
             * Uses <Get> internally.
             */
            void Do(std::function<void(T&)> func) const;

        private: //- Private members.

            /* Component <Manager>.
             *
             * The manager is where the component pointer will be taken from.
             */
            Manager& m_manager;

            /* The <OwnerId> of the component owner.
             *
             * This is who the component will be taken from.
             */
            const OwnerId m_ownerId;

            /* The <Id> of the compoent.
             *
             * This is why the <Handle> exists.
             * To access this component, if it is possible.
             */
            const Id m_componentId;
        };
    }
}

//- Inline file with template definitions.
#include "component_handle.inl"
