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
    namespace Component
    {
        class Manager
        {
        public:
            // change to vector of pairs - doesn't use any of the good features of a map right now.
            using ComponentMap = std::unordered_map< Id, UniquePtr >; 
            using EraseList = std::vector<Id>;
            using InsertList = std::vector< std::pair< Id, json11::Json > >;
            using OwnerMap = std::unordered_map< OwnerId, ComponentMap >;
            using LinkerMap = std::unordered_map< OwnerId, Linker>;

            void Erase( OwnerId ownerId, const EraseList& componentList );
            OwnerId Insert( OwnerId ownerId, const char* const filePath );
            OwnerId Insert( OwnerId ownerId, const InsertList& componentList );

        private:
            OwnerId Insert( OwnerId ownerId, ComponentMap map );

        private:
            OwnerMap m_ownerMap;
            LinkerMap m_linkerMap;
        };
    }
}
