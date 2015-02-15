#include "component_factory.h"

#include <cassert> 

namespace minmod
{
    std::unordered_map< Component::Id, ComponentFactory::CreateFunction > ComponentFactory::ms_map;
    std::unordered_map< std::string, Component::Id> ComponentFactory::ms_stringMap;

    std::shared_ptr< ComponentInterface > ComponentFactory::Create( Component::Id id )
    {
        assert( ms_map.find( id ) != ms_map.end() );
        return std::move( ms_map[ id ]() );
    }

    std::shared_ptr< ComponentInterface > ComponentFactory::Create( std::string name )
    {
        assert( ms_stringMap.find( name ) != ms_stringMap.end() );
        return std::move( Create( ms_stringMap[ name ] ) );
    }
}
