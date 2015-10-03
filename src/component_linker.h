#pragma once
//- stl.
#include <unordered_map>
#include <functional>
#include <cassert>
#include <memory>
//- minmod.
#include "component_types.h"

namespace minmod
{
    namespace component
    {
        class Interface;

        /* Componment link management.
         *
         * This stores 'on add' and 'on remove' functions all the components that an <Id> can own.
         * These functions are added via the <AddLink> functions.
         *
         * When a component is added to an <Id> the <AddComponent> function is called,
         * which will call all of the stored <AddFunc> that are assosiated with it.
         * This enables the owners of the <AddFunc> to get a pointer to the newly added component.
         *
         * The oposite case is <RemoveComponent>.
         * All the stored <RemoveFunc> assositated with the copmonent being removed are called.
         * Then, the <m_linksForIdMap> is cleaned of all of all <AddFunc> and <RemoveFunc> owned by that component.
         */
        class Linker
        {
        public: //- Public enums.

            enum class Requirement : std::uint8_t
            {
                Needed,
                Optional
            };

            enum class State : std::uint8_t
            {
                Ready,
                NotReady,
                WaitingForRequirements
            };

        public: //- Public fuctions.

            /* Destructor.
             *
             * We clean up all <RemoveFunc> upon desctruction.
             */
            ~Linker();

            /* Linking 'on add' and 'on remove' functions for a component class.
             * @add take the exact component type as a parameter
             * @remove callback for when that component is removed
             *
             * The function is templated to allow the conversion of pointers to the desired component type.
             * Internally, the <add> function is wrapped in a lambda which does a static_cast on the pointer.
             */
            template <class COMPONENT> void AddLink(std::function<void(COMPONENT* const)> add, std::function<void()> remove, Requirement requirement = Requirement::Optional);

        private: //- Private types.

            // 'On Add' callback, taking an <Interface> pointer.
            using AddFunc = std::function<void(Interface* const)>;

            // 'On Remove' callback.
            using RemoveFunc = std::function<void()>;
        
            /* The linking of one component
             *
             * All the needed functions and state to know how to link/unlink a component.
             */
            struct Link
            {
                Link(AddFunc&& add, RemoveFunc&& remove, Requirement requirement);

                AddFunc m_addFunc = nullptr;
                RemoveFunc m_removeFunc = nullptr;
                Requirement m_requirement = Requirement::Optional;
                State m_state = State::NotReady;
            };

            // Map of <Id> to <Link>.
            using LinkMap = std::unordered_map<Id, std::unique_ptr<Link>>;

            struct Links
            {
                void VerifyState();

                State m_state = State::WaitingForRequirements;
                LinkMap m_pairs;
            };

        private: //- Manager interface.

            friend class Manager;

            /* <Manager> call to link a component.
             * @interface the component to link.
             *
             * The <Linker> class need to get the interface point so it can cache it's <Id> into <m_currentlyLinking>.
             * This is don't so that when the templated <AddLink> funciton is called it doesn't have to pass it's own <Id> as a parameter.
             */
            void AddLink(Interface* const interfacePtr);


            /* <Manager> call to link a component.
             * @id the <Id> of the component being removed, the pointer isn't needed.
             *
             * Removes all <FuncPair> that this component owns.
             */
            void UnLink(const Id id);

            /* <Manager> interface for when a new component is added.
             * @interfacePtr the component being added.
             *
             * This get's the <LinkMap> 
             */
            void AddComponent(Interface* const interfacePtr);

            /* <Manager> interface for when a new component is removed.
             * @id the <Id> of the component being removed, the pointer isn't needed.
             *
             * Removes all <FuncPair> that this component owns.
             */
            void RemoveComponent(const Id id);

            /* For when the <Manager> merges two <Linker> instances
             * @linker r-value of the linker to be consumed.
             *
             * Moves all the links from the passed in <Linker> to this one.
             */
            void MoveLinks(const Linker&& linker);

        private: //- Private members.

            // Map of <Id> to <Links>.
            std::unordered_map<Id, Links> m_linksForIdMap;

            // <Id> of the component that is currently being linked.
            Id m_currentlyLinking = INVALID_ID;
        };
    }
}

//- Include the inline file for template definitions.
#include "component_linker.inl"
