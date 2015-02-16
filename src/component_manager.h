#pragma once
#ifndef MINMOD_COMPONENT__COMPONENT_MANAGER
#define MINMOD_COMPONENT__COMPONENT_MANAGER

#include <cstdint>
#include <unordered_map>
#include <memory>
#include "component_types.h"
#include "component_interface.h"

namespace minmod
{
  class ComponentManager
  {
     public:
       using ComponentMap = std::unordered_map< Component::Id, ComponentInterface::SharedPtr >;
       using OwnerMap = std::unordered_map< OwnerId, ComponentMap >;
       using ComponentList = std::vector< std::pair< Component::Id, json11::Json > >;

       OwnerId Add( OwnerId ownerId, ComponentList& componentList );
       OwnerId Add( OwnerId ownerId, const char* const filePath );
       OwnerId Add( OwnerId /*ownerId*/, Component::Id /*id*/ ) {return 0;}
       void Remove( OwnerId /*ownerId*/, Component::Id /*id*/ ) {}

     private:
       OwnerId Add( OwnerId ownerId, ComponentMap& map );

     private:
       OwnerMap m_ownerMap;
  };
}

#endif 
