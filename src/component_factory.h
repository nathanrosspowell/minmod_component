#pragma once
// stl
#include <unordered_map> 
#include <functional> 
#include <memory> 
#include <string> 
// minmod
#include "component_interface.h"

namespace minmod
{
    namespace component
    {
        class Factory
        {
        public:
            using CreateFunction = std::function<UniquePtr()>;

            template< class COMPONENT >
            static void Insert()
            {
                const auto id = COMPONENT::GetStaticId();
                ms_stringMap[ COMPONENT::GetStaticName() ] = id;
                ms_map[ id ] = [&id]()
                    {
                        return std::make_unique<COMPONENT>();
                    };
            }

            template< class COMPONENT >
            static void Erase()
            {
                ms_stringMap.erase( COMPONENT::GetStaticName() );
                ms_map.erase( COMPONENT::GetStaticId() );
            }

            static UniquePtr Create( Id id );
            static UniquePtr Create( std::string name );
            template< class COMPONENT >
            static auto Create()
            {
                return Create( COMPONENT::GetStaticId() );
            }

        private:
            static std::unordered_map< std::string, Id> ms_stringMap;
            static std::unordered_map< Id, CreateFunction > ms_map;
        };
    }
}
