#pragma once
// stl
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
// minmod
#include "component_types.h"
#include "component_interface.h"
#include "component_linker.h"
#include "component_serializer.h"

namespace minmod
{
    namespace component
    {
        class Manager : public Serializer
        {
        public:
            // Types.
            using EraseList = std::vector<Id>;
            using InsertList = std::vector<std::pair<Id, json11::Json>>;
            using ComponentMap = std::unordered_map<Id, UniquePtr>;

            struct Entry
            {
                ComponentMap m_componentMap;
                Linker m_linker;
            };
            using Map = std::unordered_map<OwnerId, Entry>;

        public:
            // Serialization.
            virtual void Deserialize(json11::Json json) override;
            virtual json11::Json Serialize() const override;

        public:
            // Functions.
            template <class COMPONENT> COMPONENT* Get(OwnerId ownerId)
            {
                return static_cast<COMPONENT*>(Get(ownerId, COMPONENT::GetStaticId()));
            }
            Interface* Get(OwnerId ownerId, Id comonentId);
            Interface* Get(OwnerId ownerId, Name componentName);
            void Erase(OwnerId ownerId, const EraseList& componentMap);
            void Erase(OwnerId ownerId);
            OwnerId Insert(OwnerId ownerId, const char* const filePath);
            OwnerId Insert(OwnerId ownerId, const json11::Json json);
            OwnerId Insert(OwnerId ownerId, const InsertList& componentMap);

        private:
            // Functions.
            OwnerId Insert(OwnerId ownerId, ComponentMap componentMap);

        private:
            // Data.
            Map m_map;
        };
    }
}
