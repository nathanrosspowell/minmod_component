#include "component_manager.h"

#include <utility>
#include <fstream>
#include <iostream> // Debug
#include "json11.hpp"
#include "component_factory.h"
namespace minmod 
{
    OwnerId ComponentManager::Add( OwnerId ownerId, ComponentList& componentList )
    {
        // Create the map.
        ComponentMap map;
        // Loop all the components.
        for ( const auto& pair : componentList )
        {
            auto comp = ComponentFactory::Create( pair.first );
            if ( comp )
            {
                comp->Deserialize( pair.second );
                map[ comp->GetId() ] = comp;
                std::cout << comp->Serialize().dump() << std::endl;
            } 
        }
        return Add( ownerId, map );
    }

    OwnerId ComponentManager::Add( OwnerId ownerId, const char* const filePath )
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
            auto name = comp["name"].string_value();
            auto c = ComponentFactory::Create( name );
            if ( c )
            {
                c->Deserialize( comp["data"] );
                map[ c->GetId() ] = c;
                std::cout << c->Serialize().dump() << std::endl;
            } 
        }
        return Add( ownerId, map );
    }

    OwnerId ComponentManager::Add( OwnerId ownerId, ComponentMap& map )
    {
        // Inform all the other components about each other.
        for ( auto& it1 : map )
        {
            for ( auto& it2 : map )
            {
                it1.second->OnAddComponent( it2.second );
            }
        }
        // Create.
        for ( auto& it: map )
        {
            it.second->Create();
        }
        // Call create.
        m_ownerMap.insert( std::make_pair( ownerId, map ) );
        return ownerId;
    }
}
