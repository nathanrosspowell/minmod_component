#ifndef MINMOD_COMPONENT__COMPONENT_MANAGER
#define MINMOD_COMPONENT__COMPONENT_MANAGER
#pragma once

#include <cstdint>
#include <unordered_map>
#include <memory>
#include "component_id.h"
#include "component_interface.h"

class ComponentManager
{
public:
    using OwnerId = std:: int32_t;
    using InterfacePtr = std::shared_ptr< ComponentInterface >;
    using ComponentMap = std::unordered_map< ComponentId::Id, InterfacePtr >;
    using OwnerMap = std::unordered_map< OwnerId, ComponentMap >;

    ComponentManager();

    OwnerId Add( OwnerId ownerId, Json );

private:
    OwnerMap m_ownerMap;
};

#endif 
