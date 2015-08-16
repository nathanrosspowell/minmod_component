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

namespace minmod
{
    namespace component
    {
        class Manager
        {
        public:
            using EraseList = std::vector<Id>;
            using InsertList = std::vector<std::pair<Id, json11::Json>>;
            using ComponentMap = std::unordered_map<Id, UniquePtr>;

            struct Entry
            {
                ComponentMap m_componentMap;
                Linker m_linker;
            };
            using Map = std::unordered_map<OwnerId, Entry>;

            template <class COMPONENT> COMPONENT* Get(OwnerId ownerId)
            {
                return static_cast<COMPONENT*>(Get(ownerId, COMPONENT::GetStaticId()));
            }
            Interface* Get(OwnerId ownerId, Id comonentId);
            Interface* Get(OwnerId ownerId, std::string componentName);
            void Erase(OwnerId ownerId, const EraseList& componentMap);
            void Erase(OwnerId ownerId);
            OwnerId Insert(OwnerId ownerId, const char* const filePath);
            OwnerId Insert(OwnerId ownerId, const InsertList& componentMap);

        private:
            OwnerId Insert(OwnerId ownerId, ComponentMap componentMap);

        private:
            Map m_map;
        };
    }
}
