#pragma once
//- stl.
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
//- minmod.
#include "component_interface.h"
//- Debug.
#include <iostream>

namespace minmod
{
    namespace component
    {
        /* A Factory for components.
         *
         * All components that are to be instansiated need to be registered in a factory.
         * Right now there is one static factory, but the goal is remove this limitation.
         */
        class Factory
        {
        public: //- Typedefs.
            
            /* The stored create function.
             *
             * All components are made from a version of this function.
             */
            using CreateFunction = std::function<UniquePtr()>;

        public: //- Public functions.

            /* Default constructor.
             *
             * Needed to allow the singleton interface.
             */
            Factory() = default;

            /* Copy constructor.
             *
             * Explicitly deleted to stop duplicate <Factory> instances.
             */
            Factory(Factory const&) = delete;

            /* Move constructor.
             *
             * Explicitly deleted to stop duplicate <Factory> instances.
             */
            Factory(Factory const&&) = delete;

            /* Assignment operator.
             *
             * Explicitly deleted to stop duplicate <Factory> instances.
             */
            void operator=(Factory const&) = delete;

            /* Move operator.
             *
             * Explicitly deleted to stop duplicate <Factory> instances.
             */
            void operator=(Factory const&&) = delete;

            /* Templated addition of a component.
             *
             * This takes all of the needed parameters from static accessor functions on the component.
             * Requirements:
             *     1) <StaticGetId> function returning an <Id>
             *     2) <StaticGetName> function returning a <Name>
             *     3) Default construcor
             * The registraion into the factory here is seen as the 'default' version of the component,
             * which will satisfy most use cases.
             *
             * Uses the non-templated <Insert> internally.
             */
            template <class T> void Insert();

            /* Addition of a component variation.
             * @id unique <Id> for the registration
             * @name unique <Name> for registration
             * @createFunc function to return the <UniquePtr>
             *
             * Adds a registraion to the <m_map>.
             *
             * The <UniquePtr> returned from the <CreateFunction> must satisfy these conditions:
             *     1) The <Interface::GetId> function must match the passed in <Id>
             *     2) The <Interface::GetName> function must match the passed in <Name>
             *
             * This is used internally by the templated version of <Insert>.
             * Unlike that version, this one has no dependecies on static functions.
             */
            void Insert(Id id, const Name& name, CreateFunction&& createFunc);

            /* Templated removal of a component.
             *
             * This matches up with the templated <Insert> function, and has the same static function requirments.
             * Uses the non-templated <Erase> internally.
             */
            template <class T> void Erase();

            /* Removal of a component variation.
             * @id an <Id> that matches the <Name> of this registraion
             * @name an <Name> that matches the <Id> of this registraion
             *
             * Removes a registion from the <m_map>.
             * Requires both parameters to make sure you have the right version.
             */
            void Erase(Id id, const Name& name);

            /* Creation via <Id>.
             *
             * This is the main usage when instantiating a new component from code.
             * The tempalte version of <Create> is easiest if you have a standard use case.
             *
             * @return std::move of a unique pointer to a new component.
             */
            UniquePtr Create(Id id);

            /* Creation via <Name>.
             *
             * This is the main usage when instantiating a new component from data.
             *
             * @return std::move of a unique pointer to a new component.
             */
            UniquePtr Create(const Name& name);
            
            /* Get an <Id> from a <Name>
             *
             * Used to allow the storage and creation of components from JSON data.
             *
             * @return the <Id> for a <Name>, or <INVALID_ID> if not found.
             */
            Id GetId(const Name& name);

        private: //- Members.

            /* <Name> to <Id> conversion map.
             *
             * Used to convert a <Name> from JSON to an <Id> so it can be created.
             */
            std::unordered_map<Name, Id> m_stringMap;

            /* <Id> to <CreateFunction> storage map.
             *
             * Use an <Id> to get the correct <CreateFunction> for the registration.
             */
            std::unordered_map<Id, CreateFunction> m_map;
        };
    }
}

//- Include the template definitions.
#include "component_factory.inl"
