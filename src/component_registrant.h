#pragma once
// minmod
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        template <class COMPONENT> class TypeRegistrant
        {
        public:
            TypeRegistrant()
            {
                TRACE("Insert component: " << COMPONENT::GetStaticName());
                Factory::GetInstance().Insert<COMPONENT>();
            }

            ~TypeRegistrant()
            {
                TRACE("Erase component: " << COMPONENT::GetStaticName());
                Factory::GetInstance().Erase<COMPONENT>();
            }
        };

        class CustomRegistrant
        {
        public:
            using Func = std::function<UniquePtr(Id, std::string)>;
            CustomRegistrant(Id id, std::string name, Func func);
            ~CustomRegistrant();

        private:
            Id m_id;
            std::string m_name;
        };
    }
}
