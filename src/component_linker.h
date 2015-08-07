#pragma once
// stl
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <vector>
// minmod
#include "component_types.h"
#include "component_interface.h"

namespace minmod
{
    namespace Component
    {
        class Linker
        {
        public:
            using OnAddMap = std::unordered_map< Id, std::function<void(Interface*)> >;
            using OnRemoveMap = std::unordered_map< Id, std::function<void()> >;

            template< class COMPONENT >
            void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove )
            {
                m_onAddMap[ COMPONENT::GetStaticId() ] = [&add](auto interfacePtr)
                {
                    auto ptr = static_cast<COMPONENT*>(interfacePtr);
                    add(ptr);
                };
                m_onRemoveMap[ COMPONENT::GetStaticId() ] = remove;
            }

        private:
            // Functions for Manager
            void Add( Id id, Interface* interfacePtr) const
            {
                auto it = m_onAddMap.find(id);
                if ( it != m_onAddMap.end() )
                {
                    it->second(interfacePtr);
                }
            }

            void Remove( Id id ) const
            {
                auto it = m_onRemoveMap.find(id);
                if ( it != m_onRemoveMap.end() )
                {
                    it->second();
                }
            }

        private:
            OnAddMap m_onAddMap;
            OnRemoveMap m_onRemoveMap;
        };
    }
}
