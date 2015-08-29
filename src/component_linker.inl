namespace minmod
{
    namespace component
    {
        template <class COMPONENT> void Linker::Link(std::function<void(COMPONENT*)> add, std::function<void()> remove)
        {
            assert(m_currentlyLinking != INVALID_ID);
            auto& ownedPairs = m_entryMap[COMPONENT::GetStaticId()];
            ownedPairs[m_currentlyLinking] = std::make_pair(
                [add](auto ptr)
                {
                    assert(dynamic_cast<COMPONENT*>(ptr) != nullptr);
                    add(static_cast<COMPONENT*>(ptr));
                },
                remove);
        }
    }
}
