#pragma once
// stl
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
// minmod
#include "component_types.h"
#include "component_interface.h"

namespace minmod
{
    namespace Component
    {
        class Manager
        {
        public:
            using ComponentMap = std::unordered_map< Id, SharedPtr >;
            using OwnerMap = std::unordered_map< OwnerId, ComponentMap >;
            using EraseComponents = std::vector<Id>;
            using InsertComponents = std::vector< std::pair< Id, json11::Json > >;

            OwnerId Insert( OwnerId ownerId, const char* const filePath );
            OwnerId Insert( OwnerId ownerId, const InsertComponents& componentList );
            void Erase( OwnerId ownerId, const EraseComponents& componentList );

        private:
            OwnerId Insert( OwnerId ownerId, const ComponentMap& map );

        private:
            OwnerMap m_ownerMap;
        };
    }
}
