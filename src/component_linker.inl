namespace minmod
{
    namespace component
    {
        template <class COMPONENT> void Linker::AddLink(std::function<void(COMPONENT*)> add, std::function<void()> remove, Requirement requirement)
        {
            AddLink(COMPONENT::GetStaticId(), add, remove, requirement);
        }

        template <class COMPONENT> void Linker::AddLink(Id componentId, std::function<void(COMPONENT*)> add, std::function<void()> remove, Requirement requirement)
        {
            assert(m_currentlyLinking != INVALID_ID);
            auto& ownedPairs = m_linksForIdMap[componentId].m_linkMap;
            auto addfunc = [add = std::move(add)](auto ptr)
                {
                    assert(dynamic_cast<COMPONENT*>(ptr) != nullptr);
                    add(static_cast<COMPONENT*>(ptr));
                };
            auto ptr = std::make_unique<Link>(addfunc, std::move(remove), requirement);
            auto pair = std::make_pair(m_currentlyLinking, std::move(ptr));
            ownedPairs.insert(std::move(pair));
        }
    }
}
