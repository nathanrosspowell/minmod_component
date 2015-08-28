namespace minmod
{
    namespace component
    {
        template <class T> T* Manager::Get(const OwnerId ownerId)
        {
            return static_cast<T*>(Get(ownerId, T::GetStaticId()));
        }
    }
}
