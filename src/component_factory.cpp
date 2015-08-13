#include "component_factory.h"
// stl
#include <cassert> 

namespace minmod
{
    namespace component
    {
        void Factory::Insert( Id id, std::string name, CreateFunction createFunc )
        {
            TRACE("Component: "<<id<<", "<<name);
            ms_stringMap.insert(std::make_pair(name, id));
            ms_map[ id ] = createFunc;
        }

        void Factory::Erase( Id id, std::string name)
        {
            TRACE("Component: "<<id<<", "<<name);
            assert( ms_stringMap[id] == name );
            ms_stringMap.erase( name );
            ms_map.erase( id );
        }

        UniquePtr Factory::Create( Id id )
        {
            assert( ms_map.find( id ) != ms_map.end() );
            return std::move( ms_map[ id ]() );
        }

        UniquePtr Factory::Create( std::string name )
        {
            assert( ms_stringMap.find( name ) != ms_stringMap.end() );
            return std::move( Create( ms_stringMap[ name ] ) );
        }
    }
}

