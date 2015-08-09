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
            void AddLink( Interface* interfacePtr) const;
            void RemoveLink( Interface* interfacePtr ) const;
            void UnLink( Id id );
            void MoveLinks( Linker&& linker );

        private:
            using AddFunc = std::function<void(Interface*)>;
            using RemoveFunc = std::function<void()>;
            using OnAddMap = std::unordered_map< Id, AddFunc>;
            using OnRemoveMap = std::unordered_map< Id, RemoveFunc >;
            OnAddMap m_onAddMap;
            OnRemoveMap m_onRemoveMap;
        };
    }
}
