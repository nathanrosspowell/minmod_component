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
                explicit Adapter(T* ptr);
                explicit operator bool() const;
                T& operator ->();
                const T& operator ->() const;

            private:
                T* const m_ptr;
                mutable bool m_checked;
            };

        public:
            Handle(Manager& manager, OwnerId ownerId);
            Handle(Manager& manager, OwnerId ownerId, Id id);

        public:
            Adapter Get() const;
            void Do(std::function<void(T&)> func) const;

        private:
            Manager& m_manager;
            const OwnerId m_ownerId;
            const Id m_componentId;
        };
    }
}

// Inline file with template definitions.
#include "component_handle.inl"
