#pragma once
// stl
#include <unordered_map> 
#include <functional> 
#include <memory> 
#include <string> 
// minmod
#include "component_interface.h"
// Debug
#include <iostream> 
using std::cout;
using std::endl;

namespace minmod
{
    namespace component
    {
        class Factory
        {
        public:
            static Factory& GetInstance()
            {
                static Factory instance;
                return instance;
            }

        public:
            using CreateFunction = std::function<UniquePtr()>;

            Factory() {}

            template< class COMPONENT > void Insert()
            {
                Insert(COMPONENT::GetStaticId(), COMPONENT::GetStaticName(), [](){return std::make_unique<COMPONENT>();});
            }
            void Insert(Id id, std::string name, CreateFunction createFunc);
            template< class COMPONENT > void Erase()
            {
                Erase( COMPONENT::GetStaticId(), COMPONENT::GetStaticName());
            }
            void Erase( Id id, std::string name );
            UniquePtr Create( Id id );
            UniquePtr Create( std::string name );
            template< class COMPONENT > auto Create()
            {
                return Create( COMPONENT::GetStaticId() );
            }
            Id GetId(std::string name);

        private:
            std::unordered_map< std::string, Id> m_stringMap;
            std::unordered_map< Id, CreateFunction > m_map;

        private:
            Factory(Factory const&) = delete;
            void operator=(Factory const&) = delete;
        };
    }
}
