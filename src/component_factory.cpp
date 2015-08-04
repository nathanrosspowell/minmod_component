#include "component_factory.h"

#include <cassert> 

namespace minmod
{
    namespace Component
    {
        std::unordered_map< Id, Factory::CreateFunction > Factory::ms_map;
        std::unordered_map< std::string, Id> Factory::ms_stringMap;

        std::shared_ptr< Interface > Factory::Create( Id id )
        {
            assert( ms_map.find( id ) != ms_map.end() );
            return std::move( ms_map[ id ]() );
        }

        std::shared_ptr< Interface > Factory::Create( std::string name )
        {
            assert( ms_stringMap.find( name ) != ms_stringMap.end() );
            return std::move( Create( ms_stringMap[ name ] ) );
        }
    }
}
