#pragma once
#ifndef MINMOD_COMPONENT__COMPONENT_MANAGER
#define MINMOD_COMPONENT__COMPONENT_MANAGER

#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
#include "component_types.h"
#include "component_interface.h"

namespace minmod
{
  class ComponentManager
  {
     public:
       using ComponentMap = std::unordered_map< Component::Id, ComponentInterface::SharedPtr >;
       using OwnerMap = std::unordered_map< OwnerId, ComponentMap >;
       using EraseComponents = std::vector<Component::Id>;
       using InsertComponents = std::vector< std::pair< Component::Id, json11::Json > >;

       OwnerId Insert( OwnerId ownerId, const char* const filePath );
       OwnerId Insert( OwnerId ownerId, const InsertComponents& componentList );
       void Erase( OwnerId ownerId, const EraseComponents& componentList );

     private:
       OwnerId Insert( OwnerId ownerId, const ComponentMap& map );

     private:
       OwnerMap m_ownerMap;
  };
}

#endif 
