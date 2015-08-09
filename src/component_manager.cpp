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
        void Manager::Erase( OwnerId ownerId, const EraseList& eraseList )
        {
            auto& entry = m_map[ ownerId ];
            auto& cl = entry.m_componentList;
            for ( const auto& removeId : eraseList )
            {
                const auto& pair = entry.m_componentList.find(removeId);
                if ( pair != entry.m_componentList.end())
                {
                    entry.m_linker.RemoveLink(pair->second.get());
                    entry.m_linker.UnLink(pair->first);
                    entry.m_componentList.erase( removeId );
                }
            }
        }

        OwnerId Manager::Insert( OwnerId ownerId, const char* const filePath )
        {
            std::ifstream in(filePath);
            std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); 
            std::string err;
            json11::Json fileJson = json11::Json::parse(file, err);
            ComponentList componentList;
            auto& jsonComponentList = fileJson["componentList"];
            for ( const auto& jsonComponent : jsonComponentList.array_items() )
            {
                auto name = jsonComponent["name"].string_value();
                auto component = Factory::Create( name );
                if ( component )
                {
                    component->Deserialize( jsonComponent["data"] );
                    std::cout << component->Serialize().dump() << std::endl;
                    componentList[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(componentList));
        }

        OwnerId Manager::Insert( OwnerId ownerId, const InsertList& insertList )
        {
            ComponentList componentList;
            for ( const auto& pair : insertList )
            {
                auto component = Factory::Create( pair.first );
                if ( component )
                {
                    component->Deserialize( pair.second );
					std::cout << component->Serialize().dump() << std::endl;
                    componentList[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(componentList) );
        }

        OwnerId Manager::Insert( OwnerId ownerId, ComponentList componentList )
        {
            auto& entry = m_map[ownerId]; // Get or create an entry.
            // Link all the existing copmonents against the new ones.
            for ( auto& pair: componentList)
            {
                entry.m_linker.AddLink(pair.second.get());
            }
            // Make a temp linker for the new components.
            Linker tempLinker;
            for ( auto& pair : componentList )
            {
                pair.second->MakeLinks(tempLinker); 
            }
            // Link all the old,
            for ( auto& pair: entry.m_componentList)
            {
                tempLinker.AddLink(pair.second.get());
            }
            // and the new components.
            for ( auto& pair: componentList)
            {
                tempLinker.AddLink(pair.second.get());
            }
            // Call create on the new components now they are linked.
            for ( auto& pair: componentList)
            {
                pair.second->Create();
            }
            // Insert the new components.
            for ( auto& pair: componentList)
            {
                entry.m_componentList[ pair.first] = std::move(pair.second);
            }
            // Add the new links to the stored linker.
            entry.m_linker.MoveLinks(std::move(tempLinker));
            return ownerId;
        }
    }
}
