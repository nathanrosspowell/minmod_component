#pragma once
// std
#include <cstdint>
// minmod
#include "component_types.h"
#include "component_manager.h"
// Debug
#include <iostream>
#include <functional>

namespace minmod
{
    namespace component
    {
        class Manager;
        template <class T> class Handle
        {
        public:
            class Adapter
            {
            public:
                explicit Adapter(T* ptr) : m_ptr(ptr), m_checked(false)
                {
                }
                explicit operator bool() const
                {
                    assert(m_checked == false);
                    m_checked = true;
                    return m_ptr != nullptr;
                }
                T& Get()
                {
                    assert(m_checked == true);
                    assert(m_ptr != nullptr);
                    return *m_ptr;
                }
                const T& Get() const
                {
                    assert(m_checked == true);
                    assert(m_ptr != nullptr);
                    return *m_ptr;
                }

            private:
                T* m_ptr;
                mutable bool m_checked;
            };

        public:
            Handle(Manager& manager, OwnerId ownerId);
            Handle(Manager& manager, OwnerId ownerId, Id id);

        public:
            Adapter Get();
            void Do(std::function<void(T&)> func);

        private:
            Manager& m_manager;
            OwnerId m_ownerId;
            Id m_componentId;
        };

        template <class T> Handle<T>::Handle(Manager& manager, OwnerId ownerId) : m_manager(manager), m_ownerId(ownerId), m_componentId(T::GetStaticId())
        {
        }

        template <class T> Handle<T>::Handle(Manager& manager, OwnerId ownerId, Id id) : m_manager(manager), m_ownerId(ownerId), m_componentId(id)
        {
        }

        template <class T> typename Handle<T>::Adapter Handle<T>::Get()
        {
            auto ptr = m_manager.Get(m_ownerId, m_componentId);
            assert(dynamic_cast<T*>(ptr) != nullptr);
            return std::move(Adapter(static_cast<T*>(ptr)));
        }

        template <class T> void Handle<T>::Do(std::function<void(T&)> func)
        {
            if (auto adapter = Get())
            {
                func(adapter.Get());
            }
        }
    }
}
