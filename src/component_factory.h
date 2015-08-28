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

            Factory()
            {
            }

            template <class COMPONENT> void Insert()
            {
                Insert(COMPONENT::GetStaticId(), COMPONENT::GetStaticName(), []()
                       {
                           return std::make_unique<COMPONENT>();
                       });
            }
            void Insert(Id id, Name name, CreateFunction createFunc);
            template <class COMPONENT> void Erase()
            {
                Erase(COMPONENT::GetStaticId(), COMPONENT::GetStaticName());
            }
            void Erase(Id id, Name name);
            UniquePtr Create(Id id);
            UniquePtr Create(Name name);
            template <class COMPONENT> auto Create()
            {
                return Create(COMPONENT::GetStaticId());
            }
            Id GetId(Name name);

        private:
            std::unordered_map<Name, Id> m_stringMap;
            std::unordered_map<Id, CreateFunction> m_map;

        private:
            Factory(Factory const&) = delete;
            void operator=(Factory const&) = delete;
        };
    }
}
