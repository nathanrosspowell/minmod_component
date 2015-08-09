#pragma once
// stl
#include <unordered_map>
#include <functional>
#include <tuple>
// minmod
#include "component_types.h"

namespace minmod
{
    namespace component
    {
        class Interface;
        class Linker
        {
        public:
            Linker();
            template< class COMPONENT >
            void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove )
            {
				m_onAddMap[COMPONENT::GetStaticId()] = std::make_tuple( m_currentlyLinking, 
                    [add](Interface* ptr) 
                    { 
                        add(static_cast<COMPONENT*>(ptr));
                    }
                );
                m_onRemoveMap[ COMPONENT::GetStaticId() ] = std::make_tuple( m_currentlyLinking, remove);
            }

        private:
            friend class Manager;
            void Link( Interface* interfacePtr);
            void Add( Interface* interfacePtr) const;
            void Remove( Interface* interfacePtr ) const;

        private:
            using AddFunc = std::function<void(Interface*)>;
            using RemoveFunc = std::function<void()>;
            using OnAddMap = std::unordered_map< Id, std::tuple< Id, AddFunc> >;
            using OnRemoveMap = std::unordered_map< Id, std::tuple< Id, RemoveFunc > >;
            OnAddMap m_onAddMap;
            OnRemoveMap m_onRemoveMap;
            Id m_currentlyLinking;
        };
    }
}
