#include "component_manager.h"

#include <utility>

ComponentManager::ComponentManager() 
{
}

auto ComponentManager::Add( OwnerId ownerId, ComponentMap& map ) -> OwnerId
{
    m_ownerMap.insert( std::make_pair( ownerId, map ) );
    return ownerId;
}
