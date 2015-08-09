#pragma once
// stl
#include <unordered_map>
#include <functional>
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
            ~Linker();
            template< class COMPONENT >
            void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove )
            {
				m_onAddMap[COMPONENT::GetStaticId()][m_currentlyLinking] = 
                    [add](Interface* ptr) 
                    { 
                        add(static_cast<COMPONENT*>(ptr));
                    };
                m_onRemoveMap[ COMPONENT::GetStaticId() ][m_currentlyLinking] = remove;
            }

        private:
            friend class Manager;
            void Link( Interface* interfacePtr);
            void UnLink( Id id );
            void AddComponent( Interface* interfacePtr) const;
            void RemoveComponent( Id id);
            void MoveLinks( Linker&& linker );

        private:
            using AddFunc = std::function<void(Interface*)>;
            using RemoveFunc = std::function<void()>;
            using AddMap = std::unordered_map< Id, AddFunc >;
            using RemoveMap = std::unordered_map< Id, RemoveFunc >;
            using OnAddMap = std::unordered_map< Id, AddMap>;
            using OnRemoveMap = std::unordered_map< Id, RemoveMap>;
            OnAddMap m_onAddMap;
            OnRemoveMap m_onRemoveMap;
            Id m_currentlyLinking;
        };
    }
}
