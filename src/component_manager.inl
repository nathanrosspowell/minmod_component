namespace minmod
{
    namespace component
    {
        template <class T> const T* Manager::Get(const OwnerId ownerId) const
        {
            return static_cast<const T*>(Get(ownerId, T::GetStaticId()));
        }

        template <class T> T* Manager::Get(const OwnerId ownerId)
        {
            return static_cast<T*>(Get(ownerId, T::GetStaticId()));
        }
    }
}
