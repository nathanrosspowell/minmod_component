#pragma once
#include <unordered_map> 
#include <functional> 
#include <string> 
#include "component_interface.h"

namespace minmod
{
    namespace Component
    {
        class Factory
        {
        public:
            using CreateFunction = std::function<SharedPtr()>;

            template< class COMPONENT >
            static void Insert()
            {
                const auto id = COMPONENT::GetStaticId();
                ms_stringMap[ COMPONENT::GetStaticName() ] = id;
                ms_map[ id ] = [&id]()
                    {
                        SharedPtr ptr;
                        ptr.reset(new COMPONENT());
                        return ptr;
                    };
            }

            template< class COMPONENT >
            static void Erase()
            {
                ms_stringMap.erase( COMPONENT::GetStaticName() );
                ms_map.erase( COMPONENT::GetStaticId() );
            }

            static std::shared_ptr< Interface > Create( Id id );
            static std::shared_ptr< Interface > Create( std::string name );
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
