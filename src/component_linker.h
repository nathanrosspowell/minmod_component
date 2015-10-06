#pragma once
//- stl.
#include <unordered_map>
#include <functional>
#include <cassert>
#include <memory>
#include <vector>
//- minmod.
#include "component_types.h"

namespace minmod
{
    namespace component
    {
        class Interface;
        class Manager;

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

            /* Requiremnt levels.
             *
             * Some links might be optional, some might be needed.
             */
            enum class Requirement : std::uint8_t
            {
                Needed, //- This link is important for functionality of the component.
                Optional //- Not needed for main function.
            };

            /* A state of readyness.
             *
             * Options for readyness state.
             */
            enum class State : std::uint8_t
            {
                Ready, //- 100% ready.
                NotReady, //- Was ready, but now is not.
                WaitingForRequirements //- Never been ready.
            };

        public: //- Public fuctions.

            /* Constructor.
             *
             * This has to be made with a reference to it's manager.
             */
            explicit Linker(Manager& manager);

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

            /* Linking 'on add' and 'on remove' functions for a component class.
             * @componentId the id passed explicitly, not taked form the template parameters
             * @add take the exact component type as a parameter
             * @remove callback for when that component is removed
             *
             * The same as th other AddLink, but without the static id function dependency.
             */
            template <class COMPONENT> void AddLink(Id componentId, std::function<void(COMPONENT* const)> add, std::function<void()> remove, Requirement requirement = Requirement::Optional);

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
                /* Construct all the data of a link between components.
                 * @add function to call on add.
                 * @remove function to call on remove.
                 * @requirement if this link is <Requirement::Needed> or not.
                 *
                 * Holds how to add and remove the link and the current state of the link.
                 */
                Link(AddFunc&& add, RemoveFunc&& remove, Requirement requirement);

                // Function to call when the needed <Interface> is added.
                AddFunc m_addFunc = nullptr;

                // Function to call when the needed <Interface> is removed.
                RemoveFunc m_removeFunc = nullptr;

                // If this link is a <Requirement> for the owning component to function.
                Requirement m_requirement = Requirement::Optional;

                // The current <State> of this link.
                State m_state = State::NotReady;
            };

            /* Wrapper for the link data for an <Interface>.
             *
             * 
             */
            struct Links
            {
                // <State> of the links for this component.
                State m_state = State::WaitingForRequirements;
                
                // Map of <Id> to <Link>.
                std::unordered_map<Id, std::unique_ptr<Link>> m_linkMap;

                // List of <Id> to verify the state of the component.
                std::vector<Id> m_ownedLinks;
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

            /*
             *
             */
            void VerifyLinks();

        private: //- Private members.

            // Refference to the <Manager> that owns this.
            Manager& m_manager;

            // Map of <Id> to <Links>.
            std::unordered_map<Id, Links> m_linksForIdMap;

            // <Id> of the component that is currently being linked.
            Id m_currentlyLinking = INVALID_ID;
        };
    }
}

//- Include the inline file for template definitions.
#include "component_linker.inl"
