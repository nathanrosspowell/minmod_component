#pragma once
//- stl.
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
//- minmod.
#include "component_types.h"
#include "component_interface.h"
#include "component_linker.h"
#include "component_serializer.h"

namespace minmod
{
    namespace component
    {
        class Factory;

        /* A mapping of <OwnerId> to many component <Interface> instances.
         *
         * All components will be added, retrieved and removed via this class.
         */
        class Manager : public Serializer
        {
        public: //- Types.

            // List of <Id> that will be erased.
            using EraseList = std::vector<Id>;

            // List of <Id> to <json11::Json> pairs.
            using InsertList = std::vector<std::pair<Id, json11::Json>>;

            // Map of <Id> to <UniquePtr>.
            using ComponentMap = std::unordered_map<Id, UniquePtr>;

        public: //- Serialization.

            // @inherit
            virtual void Deserialize(const json11::Json& json) override;

            // @inherit
            virtual json11::Json Serialize() const override;

        public: //- Public functions.

            /* Constructor
             *
             * Every <Manager> needs to have a factory refference.
             */
            explicit Manager(Factory& factory);

            /* Get a <Interface> pointer for a component.
             *
             * This is a way to get a component pointer via a the static function <GetStaticId>.
             * 
             * @return an <Interface> pointer which can be `nullptr`.
             */
            template <class T> const T* Get(const OwnerId ownerId) const;
            template <class T> T* Get(const OwnerId ownerId);

            /* Get a <Interface> pointer for a component.
             *
             * This is a way to get a component pointer via it's <Id>.
             * 
             * @return an <Interface> pointer which can be `nullptr`.
             */
            const Interface* Get(const OwnerId ownerId, const Id comonentId) const;
            Interface* Get(const OwnerId ownerId, const Id comonentId);

            /* Get a <Interface> pointer for a component.
             *
             * This is a way to get a component pointer via name.
             * 
             * @return an <Interface> pointer which can be `nullptr`.
             */
            const Interface* Get(const OwnerId ownerId, const Name& componentName) const;
            Interface* Get(const OwnerId ownerId, const Name& componentName);

            /* Removal of one or many components.
             *
             * This is how to add remove components with an <EraseList>.
             */
            void Erase(const OwnerId ownerId, const EraseList& componentMap);

            /* Removal of an entire entry.
             *
             * This removes all components and the <OwnerId> from the class.
             */
            void Erase(const OwnerId ownerId);

            /* Insert of one or many components.
             *
             * This is how to add components via a JSON data filename.
             *
             * @return <OwnerId>
             */
            OwnerId Insert(const OwnerId ownerId, const char* const filePath);

            /* Insert of one or many components.
             *
             * This is how to add components via a <json11::Json>.
             *
             * @return <OwnerId>.
             */
            OwnerId Insert(const OwnerId ownerId, const json11::Json& json);

            /* Insert of one or many components.
             *
             * This is how to add components via an <InsertList>
             *
             * @return <OwnerId>.
             */
            OwnerId Insert(const OwnerId ownerId, const InsertList& componentMap);

        private: //- Private structures.

            /* The entry for each <OwnerId> in the <Manager>.
             *
             */
            struct Entry
            {
                Entry(Manager& manager) : m_linker(manager) {}

                // The links between all of the owners components.
                Linker m_linker;

                // Storage of all the owners <UniquePtr>.
                ComponentMap m_componentMap;
            };

        private: //- Private functions.

            friend class Linker;

            /* Insert of one or many components.
             *
             * This is how to add components via a <ComponentMap> r-value.
             * All other <Insert> functions call this one internally.
             *
             * @return <OwnerId>.
             */
            OwnerId Insert(const OwnerId ownerId, ComponentMap&& componentMap);

            Entry& GetOrCreateEntry(OwnerId ownerId);

            void SetReady(Id componentId);

            void SetNotReady(Id componentId);

        private: //- Private members.

            // A map of <OwnerId> to <Entry>.
            std::unordered_map<OwnerId, std::unique_ptr<Entry>> m_entryMap;

            // <Factory> refference.
            Factory& m_factory;
        };
    }
}

// Inline file for template declarations.
#include "component_manager.inl"
