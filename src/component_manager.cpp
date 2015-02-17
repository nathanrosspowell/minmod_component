#include "component_manager.h"

#include <utility>
#include <fstream>
#include "json11.hpp"
#include "component_factory.h"

#include <iostream> // Debug

namespace minmod 
{
    OwnerId ComponentManager::Add( OwnerId ownerId, const char* const filePath )
    {
        std::ifstream in(filePath);
        std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); 
        std::string err;
        json11::Json fileJson = json11::Json::parse(file, err);
        ComponentMap map;
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

    OwnerId ComponentManager::Add( OwnerId ownerId, const AddComponents& componentList )
    {
        ComponentMap map;
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

    void ComponentManager::Remove( OwnerId ownerId, const RemoveComponents& componentList )
    {
        auto& map = m_ownerMap[ ownerId ];
        for ( const auto& removeId : componentList )
        {
            auto& removeComp = map[ removeId ];
            for ( auto& it : map )
            {
                it.second->OnRemoveComponent( removeComp );
            }
            map.erase( removeId );
        }
    }

    OwnerId ComponentManager::Add( OwnerId ownerId, const ComponentMap& map )
    {
        for ( auto& it1 : map )
        {
            for ( auto& it2 : map )
            {
                it1.second->OnAddComponent( it2.second );
            }
        }
        for ( auto& it: map )
        {
            it.second->Create();
        }
        m_ownerMap.insert( std::make_pair( ownerId, map ) );
        return ownerId;
    }
}
