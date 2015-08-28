namespace minmod
{
    namespace component
    {
        template <class T> void Factory::Insert()
        {
            Insert(T::GetStaticId(), T::GetStaticName(), []()
                   {
                       return std::make_unique<T>();
                   });
        }

        template <class T> void Factory::Erase()
        {
            Erase(T::GetStaticId(), T::GetStaticName());
        }

        template <class T> auto Factory::Create()
        {
            return Create(T::GetStaticId());
        }
    }
}
