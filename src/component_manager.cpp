#include "component_manager.h"
// stl
#include <utility>
#include <fstream>
// json
#include "json11.hpp"
// minmod
#include "component_factory.h"
#include "component_types.h"
#include "component_interface.h"
// Debug
#include <iostream> 

namespace minmod 
{
    namespace Component
    {
        void Manager::Erase( OwnerId ownerId, const EraseList& componentList )
        {
            auto& map = m_ownerMap[ ownerId ];
            for ( const auto& removeId : componentList )
            {
                auto& removeComp = map[ removeId ];
                for ( auto& it : map )
                {
                    //it.second->OnEraseComponent( removeComp.get() );
                }
                map.erase( removeId );
            }
        }

        OwnerId Manager::Insert( OwnerId ownerId, const char* const filePath )
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
                auto component = Factory::Create( name );
                if ( component )
                {
                    component->Deserialize( comp["data"] );
                    std::cout << component->Serialize().dump() << std::endl;
                    map[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(map));
        }

        OwnerId Manager::Insert( OwnerId ownerId, const InsertList& componentList )
        {
            ComponentMap map;
            for ( const auto& pair : componentList )
            {
                auto component = Factory::Create( pair.first );
                if ( component )
                {
                    component->Deserialize( pair.second );
                    map[ component->GetId() ] = std::move(component);
                    std::cout << component->Serialize().dump() << std::endl;
                } 
            }
            return Insert( ownerId, std::move(map) );
        }

        OwnerId Manager::Insert( OwnerId ownerId, ComponentMap map )
        {
            auto currentComponent = m_ownerMap.find(ownerId);
            if ( currentComponent != m_ownerMap.end()) 
            {
                Linker subLinker;
                // Set up all links, then pass all knows components, then 'create'/'inpair'
                for ( auto& pair : map )
                {
                    pair.second->MakeLinks(subLinker);
                }
                auto& currentMap = currentComponent->second;
                for ( auto& pair : currentMap )
                {
                    subLinker.Add(pair.second.get());
                }
            }
            auto& linker = m_linkerMap[ownerId];
            for ( auto& pair: map )
            {
                pair.second->MakeLinks(linker); 
            }
            for ( auto& pair: map )
            {
                linker.Add(pair.second.get());
            }
            for ( auto& pair: map )
            {
                pair.second->Create();
            }
            m_ownerMap.insert( std::make_pair( ownerId, std::move(map) ) );
            return ownerId;
        }
    }
}
