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
            m_stringMap.insert(std::make_pair(name, id));
            m_map[ id ] = createFunc;
        }

        void Factory::Erase( Id id, std::string name)
        {
            TRACE("Component: "<<id<<", "<<name);
			assert(m_stringMap[name] == id);
            m_stringMap.erase( name );
            m_map.erase( id );
        }

        UniquePtr Factory::Create( Id id )
        {
            assert( m_map.find( id ) != m_map.end() );
            return std::move( m_map[ id ]() );
        }

        UniquePtr Factory::Create( std::string name )
        {
            assert( m_stringMap.find( name ) != m_stringMap.end() );
            return std::move( Create( m_stringMap[ name ] ) );
        }

        Id Factory::GetId(std::string name)
        {
            auto idIt = m_stringMap.find(name);
            if ( idIt != m_stringMap.end())
            {
                return idIt->second;
            }
            return INVALID_ID;
        }
    }
}

