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
            using InsertList = std::vector< std::pair< Id, json11::Json > >;
            using ComponentList = std::unordered_map< Id, UniquePtr>;

            struct Entry
            {
                ComponentList m_componentList;
                Linker m_linker;
            };
            using Map = std::unordered_map< OwnerId, Entry >;

            void Erase( OwnerId ownerId, const EraseList& componentList );
            OwnerId Insert( OwnerId ownerId, const char* const filePath );
            OwnerId Insert( OwnerId ownerId, const InsertList& componentList );

        private:
            OwnerId Insert( OwnerId ownerId, ComponentList componentList );

        private:
            Map m_map;
        };
    }
}
