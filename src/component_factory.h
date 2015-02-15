#ifndef MINMOD_COMPONENT__COMPONENT_FACTORY
#define MINMOD_COMPONENT__COMPONENT_FACTORY
#pragma once

#include <unordered_map> 
#include <functional> 
#include <string> 
#include "component_interface.h"

#include <iostream> // Debug

namespace minmod
{
    class ComponentFactory
    {
    public:
        using CreateFunction = std::function<std::shared_ptr< ComponentInterface >()>;

        template< class COMPONENT >
        static void Insert()
        {
            const auto id = COMPONENT::GetStaticId();
            ms_stringMap[ COMPONENT::GetStaticName() ] = id;
            std::cout << "  Insert : " << id <<  " name : " << COMPONENT::GetStaticName() << std::endl;
            ms_map[ id ] = [&id]()
                {
                    std::cout << "  Create: 1 " << id << std::endl;
                    std::shared_ptr<ComponentInterface> ptr;
                    std::cout << "  Create: 2 " << id << std::endl;
                    ptr.reset(new COMPONENT());
                    std::cout << "  Create: 3 " << id << std::endl;
                    return ptr;
                };
        }

        template< class COMPONENT >
        static void Erase()
        {
            ms_stringMap.erase( COMPONENT::GetStaticName() );
            ms_map.erase( COMPONENT::GetStaticId() );
        }

        template< class COMPONENT >
        static std::shared_ptr< ComponentInterface > Create()
        {
            return Create( COMPONENT::GetStaticId() );
        }

        static std::shared_ptr< ComponentInterface > Create( Component::Id id );
        static std::shared_ptr< ComponentInterface > Create( std::string name );

    private:
        static std::unordered_map< std::string, Component::Id> ms_stringMap;
        static std::unordered_map< Component::Id, CreateFunction > ms_map;
    };

}

#endif
