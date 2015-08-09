#include "component_factory.h"
// stl
#include <cassert> 

namespace minmod
{
    namespace component
    {
        std::unordered_map< Id, Factory::CreateFunction > Factory::ms_map;
        std::unordered_map< std::string, Id> Factory::ms_stringMap;

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
