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

            Factory() = default;
            Factory(Factory const&) = delete;
            void operator=(Factory const&) = delete;

            template <class T> void Insert();
            void Insert(Id id, const Name& name, CreateFunction createFunc);
            template <class T> void Erase();
            void Erase(Id id, const Name&  name);
            UniquePtr Create(Id id);
            UniquePtr Create(const Name&  name);
            template <class T> auto Create();
            Id GetId(const Name&  name);

        private:
            std::unordered_map<Name, Id> m_stringMap;
            std::unordered_map<Id, CreateFunction> m_map;
        };
    }
}

// Include the template definitions.
#include "component_factory.inl"
