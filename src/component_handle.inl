namespace minmod
{
    namespace component
    {
        template <class T> Handle<T>::Adapter::Adapter(T* ptr) : m_ptr(ptr), m_checked(false)
        {
        }

        template <class T> Handle<T>::Adapter::operator bool() const
        {
            assert(m_checked == false);
            m_checked = true;
            return m_ptr != nullptr;
        }

        template <class T> T* Handle<T>::Adapter::operator->()
        {
            assert(m_checked == true);
            assert(m_ptr != nullptr);
            return m_ptr;
        }

        template <class T> const T* Handle<T>::Adapter::operator->() const
        {
            assert(m_checked == true);
            assert(m_ptr != nullptr);
            return m_ptr;
        }

        template <class T> T& Handle<T>::Adapter::Get()
        {
            assert(m_checked == true);
            assert(m_ptr != nullptr);
            return *m_ptr;
        }

        template <class T> const T& Handle<T>::Adapter::Get() const
        {
            assert(m_checked == true);
            assert(m_ptr != nullptr);
            return *m_ptr;
        }

        template <class T> Handle<T>::Handle(Manager& manager, OwnerId ownerId, Id id) : m_manager(manager), m_ownerId(ownerId), m_componentId(id)
        {
        }

        template <class T> Handle<T>::Handle(Manager& manager, OwnerId ownerId) : m_manager(manager), m_ownerId(ownerId), m_componentId(T::GetStaticId())
        {
        }

        template <class T> auto Handle<T>::Get() const -> Adapter
        {
            auto ptr = m_manager.Get(m_ownerId, m_componentId);
            assert(dynamic_cast<T*>(ptr) != nullptr);
            return std::move(Adapter(static_cast<T*>(ptr)));
        }

        template <class T> void Handle<T>::Do(std::function<void(T&)> func) const
        {
            if (auto adapter = Get())
            {
                func(adapter.Get());
            }
        }
    }
}
