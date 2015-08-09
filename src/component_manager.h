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
            // change to vector of pairs - doesn't use any of the good features of a map right now.
            using Components = std::unordered_map< Id, UniquePtr >; 
            using EraseList = std::vector<Id>;
            using InsertList = std::vector< std::pair< Id, json11::Json > >;
            using OwnerMap = std::unordered_map< OwnerId, Components >;
            using LinkerMap = std::unordered_map< OwnerId, Linker>;
            using Map = std::unordered_map< OwnerId, std::tuple<Components, Linker>>;

            void Erase( OwnerId ownerId, const EraseList& componentList );
            OwnerId Insert( OwnerId ownerId, const char* const filePath );
            OwnerId Insert( OwnerId ownerId, const InsertList& componentList );

        private:
            OwnerId Insert( OwnerId ownerId, Components map );

        private:
            OwnerMap m_ownerMap;
            LinkerMap m_linkerMap;
            Map m_map;
        };
    }
}
