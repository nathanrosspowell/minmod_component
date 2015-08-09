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
    namespace component
    {
        void Manager::Erase( OwnerId ownerId, const EraseList& componentList )
        {
            auto& map = m_map[ ownerId ];
            auto& components = std::get<Components>(map);
            auto& linker = std::get<Linker>(map);
            for ( const auto& removeId : componentList )
            {
                const auto& pair = components.find(removeId);
                if ( pair != components.end())
                {
                    linker.Remove(pair->second.get());
                    components.erase( removeId );
                }
            }
        }

        OwnerId Manager::Insert( OwnerId ownerId, const char* const filePath )
        {
            std::ifstream in(filePath);
            std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); 
            std::string err;
            json11::Json fileJson = json11::Json::parse(file, err);
            Components components;
            auto& jsonComponents = fileJson["components"];
            for ( const auto& jsonComponent : jsonComponents.array_items() )
            {
                auto name = jsonComponent["name"].string_value();
                auto component = Factory::Create( name );
                if ( component )
                {
                    component->Deserialize( jsonComponent["data"] );
                    std::cout << component->Serialize().dump() << std::endl;
                    components[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(components));
        }

        OwnerId Manager::Insert( OwnerId ownerId, const InsertList& componentList )
        {
            Components components;
            for ( const auto& pair : componentList )
            {
                auto component = Factory::Create( pair.first );
                if ( component )
                {
                    component->Deserialize( pair.second );
					std::cout << component->Serialize().dump() << std::endl;
                    components[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(components) );
        }

        OwnerId Manager::Insert( OwnerId ownerId, Components componentMap )
        {
            auto currentComponent = m_ownerMap.find(ownerId);
            bool alreadyInMap = currentComponent != m_ownerMap.end();
            if ( alreadyInMap ) 
            {
                Linker subLinker;
                // Set up all links, then pass all knows components, then 'create'/'inpair'
                for ( auto& pair : componentMap )
                {
                    subLinker.Link(pair.second.get());
                }
                auto& currentMap = currentComponent->second;
                for ( auto& pair : currentMap )
                {
                    subLinker.Add(pair.second.get());
                }
            }
            auto& map = m_map[ownerId];
            auto& components = std::get<Components>(map);
            auto& linker = std::get<Linker>(map);
            for ( auto& pair: components )
            {
                linker.Link(pair.second.get());
            }
            for ( auto& pair: components )
            {
                linker.Add(pair.second.get());
            }
            for ( auto& pair: components )
            {
                pair.second->Create();
            }
            m_ownerMap.insert( std::make_pair( ownerId, std::move(components) ) );
            return ownerId;
        }
    }
}
