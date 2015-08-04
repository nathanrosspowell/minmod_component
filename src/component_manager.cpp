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
                auto c = Factory::Create( name );
                if ( c )
                {
                    c->Deserialize( comp["data"] );
                    map[ c->GetId() ] = c;
                    std::cout << c->Serialize().dump() << std::endl;
                } 
            }
            return Insert( ownerId, map );
        }

        OwnerId Manager::Insert( OwnerId ownerId, const InsertComponents& componentList )
        {
            ComponentMap map;
            for ( const auto& pair : componentList )
            {
                auto comp = Factory::Create( pair.first );
                if ( comp )
                {
                    comp->Deserialize( pair.second );
                    map[ comp->GetId() ] = comp;
                    std::cout << comp->Serialize().dump() << std::endl;
                } 
            }
            return Insert( ownerId, map );
        }

        void Manager::Erase( OwnerId ownerId, const EraseComponents& componentList )
        {
            auto& map = m_ownerMap[ ownerId ];
            for ( const auto& removeId : componentList )
            {
                auto& removeComp = map[ removeId ];
                for ( auto& it : map )
                {
                    it.second->OnEraseComponent( removeComp );
                }
                map.erase( removeId );
            }
        }

        OwnerId Manager::Insert( OwnerId ownerId, const ComponentMap& map )
        {
            for ( auto& it1 : map )
            {
                for ( auto& it2 : map )
                {
                    it1.second->OnInsertComponent( it2.second );
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
}
