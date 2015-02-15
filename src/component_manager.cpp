#include "component_manager.h"

#include <utility>
#include <fstream>
#include <iostream> // Debug
#include "json11.hpp"
#include "component_factory.h"
namespace minmod 
{
    ComponentManager::ComponentManager() 
    {
    }

    auto ComponentManager::Add( OwnerId ownerId, ComponentMap& map ) -> OwnerId
    {
        m_ownerMap.insert( std::make_pair( ownerId, map ) );
        return ownerId;
    }

    auto ComponentManager::Add( OwnerId ownerId, const char* const filePath ) -> OwnerId
    {
        // Get the json structure.
        std::ifstream in(filePath);
        std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); 
        std::string err;
        json11::Json fileJson = json11::Json::parse(file, err);
        // Create the map.
        ComponentMap map;
        // Loop all the components.
        auto& comps = fileJson["components"];
        for ( const auto& comp : comps.array_items() )
        {
            /*
            auto name = comp["name"].string_value();
            auto c = ComponentFactory::Create( name );
            c->Deserialize( comp["data"] );
            map[ c->GetId() ] = c;
            */
        }
        // Insert the map.
        m_ownerMap.insert( std::make_pair( ownerId, map ) );
        return ownerId;
    }
}
