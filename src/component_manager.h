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

       ComponentManager();

       OwnerId Add( OwnerId ownerId, ComponentMap& map );
       OwnerId Add( OwnerId ownerId, const char* const filePath );
       OwnerId Add( OwnerId /*ownerId*/, Component::Id /*id*/ ) {return 0;}
       void Remove( OwnerId /*ownerId*/, Component::Id /*id*/ ) {}

     private:
       OwnerMap m_ownerMap;
  };
}

#endif 
