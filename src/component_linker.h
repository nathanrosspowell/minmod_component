#pragma once
// stl
#include <unordered_map>
#include <functional>
// minmod
#include "component_types.h"

namespace minmod
{
    namespace Component
    {
        class Interface;
        class Linker
        {
        public:
            template< class COMPONENT >
            void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove )
            {
				m_onAddMap[COMPONENT::GetStaticId()] = [add](Interface* ptr) 
                    { 
                        add(static_cast<COMPONENT*>(ptr));
                    };
                m_onRemoveMap[ COMPONENT::GetStaticId() ] = remove;
            }

        private:
            friend class Manager;
            void Add( Interface* interfacePtr) const;
            void Remove( Interface* interfacePtr ) const;

        private:
            using OnAddMap = std::unordered_map< Id, std::function<void(Interface*)> >;
            using OnRemoveMap = std::unordered_map< Id, std::function<void()> >;
            OnAddMap m_onAddMap;
            OnRemoveMap m_onRemoveMap;
        };
    }
}
