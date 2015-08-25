#pragma once
// std
#include <cstdint>
// minmod
#include "component_types.h"
#include "component_manager.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        template <class T>
        class Handle
        {
        public:
            Handle(Manager& manager, OwnerId ownerId, Id id )
                : m_manager(manager)
                , m_ownerId(ownerId)
                , m_componentId(id)
            {
            }

        public:
            std::pair<bool, T*> Get()
            {
                auto ptr = m_manager.Get(m_ownerId, m_componentId);
                return std::make_pair( ptr != nullptr, static_cast<T*>(ptr));
            }
            void Do(std::function<void(T&)> func)
            {
                auto pair = Get();
                if ( pair.first )
                {
                    func(static_cast<T&>(*pair.second));
                }
            }

        private:
            Manager& m_manager;
            OwnerId m_ownerId;
            Id m_componentId;
        };
    }
}
