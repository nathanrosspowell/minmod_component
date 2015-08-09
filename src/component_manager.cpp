#include "component_manager.h"
// stl
#include <utility>
#include <fstream>
#include <cassert>
// json
#include "json11.hpp"
// minmod
#include "component_factory.h"
#include "component_types.h"
#include "component_interface.h"
// Debug
#include <iostream> 
using std::cout;
using std::endl;

namespace minmod 
{
    namespace component
    {
        void Manager::Erase( OwnerId ownerId, const EraseList& eraseList )
        {
            TRACE("For ownerId: "<<ownerId<<". "<<eraseList.size()<<" to remove");
            assert(ownerId != INVALID_ID);
            auto& entry = m_map[ ownerId ];
            for ( const auto& removeId : eraseList )
            {
                const auto& pair = entry.m_componentMap.find(removeId);
                assert(pair != entry.m_componentMap.end());
                entry.m_linker.RemoveComponent(pair->first);
                entry.m_linker.UnLink(pair->first);
                entry.m_componentMap.erase( removeId );
            }
        }

        OwnerId Manager::Insert( OwnerId ownerId, const char* const filePath )
        {
            TRACE("For ownerId: "<<ownerId<<". From filePath: "<<filePath);
            assert(ownerId != INVALID_ID);
            std::ifstream in(filePath);
            std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); 
            std::string err;
            json11::Json fileJson = json11::Json::parse(file, err);
            ComponentMap componentMap;
            auto& jsonComponentMap = fileJson["components"];
            assert(jsonComponentMap.array_items().size() > 0);
            for ( const auto& jsonComponent : jsonComponentMap.array_items() )
            {
                auto name = jsonComponent["name"].string_value();
                auto component = Factory::Create( name );
                if ( component )
                {
                    component->Deserialize( jsonComponent["data"] );
                    TRACE("  Deserialize of: "<<component->GetName());
                    TRACE("    "<<component->Serialize().dump());
                    componentMap[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(componentMap));
        }

        OwnerId Manager::Insert( OwnerId ownerId, const InsertList& insertList )
        {
            TRACE("For ownerId: "<<ownerId<<". "<<insertList.size()<<" to insert");
            assert(ownerId != INVALID_ID);
            assert(insertList.size() > 0);
            ComponentMap componentMap;
            for ( const auto& pair : insertList )
            {
                auto component = Factory::Create( pair.first );
                if ( component )
                {
                    component->Deserialize( pair.second );
                    TRACE("  Deserialize of: "<<component->GetName());
                    TRACE("    "<<component->Serialize().dump());
                    componentMap[ component->GetId() ] = std::move(component);
                } 
            }
            return Insert( ownerId, std::move(componentMap) );
        }

        OwnerId Manager::Insert( OwnerId ownerId, ComponentMap componentMap )
        {
            assert(ownerId != INVALID_ID);
            assert(componentMap.size() > 0);
            auto& entry = m_map[ownerId]; // Get or create an entry.
            // Link all the existing copmonents against the new ones.
            for ( auto& pair: componentMap)
            {
                entry.m_linker.AddComponent(pair.second.get());
            }
            // Make a temp linker for the new components.
            Linker tempLinker;
            for ( auto& pair : componentMap )
            {
				tempLinker.Link(pair.second.get());
            }
            // Link all the old,
            for ( auto& pair: entry.m_componentMap)
            {
                tempLinker.AddComponent(pair.second.get());
            }
            // and the new components.
            for ( auto& pair: componentMap)
            {
                tempLinker.AddComponent(pair.second.get());
            }
            // Call create on the new components now they are linked.
            for ( auto& pair: componentMap)
            {
                pair.second->Create();
            }
            // Insert the new components.
            for ( auto& pair: componentMap)
            {
                assert(entry.m_componentMap.find(pair.first) == entry.m_componentMap.end());
                entry.m_componentMap[ pair.first] = std::move(pair.second);
            }
            // Add the new links to the stored linker.
            entry.m_linker.MoveLinks(std::move(tempLinker));
            return ownerId;
        }
    }
}
