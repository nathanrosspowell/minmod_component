#include "component_linker.h"
// stl
#include <algorithm>
// minmod
#include "component_interface.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        Linker::Link::Link(AddFunc&& add, RemoveFunc&& remove, Requirement requirement)
            : m_addFunc(add)
            , m_removeFunc(remove)
            , m_requirement(requirement)
        {
        }

        void Linker::Links::VerifyState()
        {
            if (m_state == State::Ready )
            {
                return;
            }
            bool ready = true;
            for ( const auto& pair : m_pairs)
            {
                const auto linkage = pair.second.get();
                if ( linkage->m_requirement == Requirement::Needed && linkage->m_state != State::Ready )
                {
                    ready = false;
                    break;
                }
            }
            if (ready)
            {
                m_state = State::Ready;
            }
        }

        Linker::~Linker()
        {
            TRACE("Clean up Linker");
            // Correctly call all of the 'on remove' functions.
            for (const auto& pair : m_linksForIdMap)
            {
                RemoveComponent(pair.first);
            }
            // Loop all of the entries until they are all gone.
            auto it = m_linksForIdMap.begin();
            while (it != m_linksForIdMap.end())
            {
                UnLink(it->first);
                it = m_linksForIdMap.erase(it);
            }
        }

        void Linker::AddLink(Interface* const interfacePtr)
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: " << interfacePtr->GetName() << ", Id: " << interfacePtr->GetId());
            // Set the current Id so that it's one less paramter to pass.
            m_currentlyLinking = interfacePtr->GetId();
            interfacePtr->MakeLinks(*this);
            m_currentlyLinking = INVALID_ID;
        }

        void Linker::UnLink(const Id id)
        {
            assert(id != INVALID_ID);
            TRACE("Id: " << id);
            for (auto& pair : m_linksForIdMap)
            {
                pair.second.m_pairs.erase(id);
            }
        }

        void Linker::AddComponent(Interface* const interfacePtr) 
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: " << interfacePtr->GetName() << ", Id: " << interfacePtr->GetId());
            auto it = m_linksForIdMap.find(interfacePtr->GetId());
            if (it != m_linksForIdMap.end())
            {
                for (const auto& ownedPair : it->second.m_pairs)
                {
                    auto& addFunc = ownedPair.second->m_addFunc;
                    addFunc(interfacePtr);
                }
                it->second.VerifyState();
            }
        }

        void Linker::RemoveComponent(const Id id)
        {
            TRACE("Id: " << id);
            assert(id != INVALID_ID);
            auto it = m_linksForIdMap.find(id);
            if (it != m_linksForIdMap.end())
            {
                for (const auto& funcPair : it->second.m_pairs)
                {
                    auto& removeFunc = funcPair.second->m_removeFunc;
                    removeFunc();
                }
            }
            // Unlink anything this component is linked against.
            for (auto& pair : m_linksForIdMap)
            {
                for (const auto& ownedPair : pair.second.m_pairs)
                {
                    if (ownedPair.first == id)
                    {
                        auto& removeFunc = ownedPair.second->m_removeFunc;
                        removeFunc();
                    }
                }
                pair.second.VerifyState();
            }
        }

        void Linker::MoveLinks(const Linker&& linker)
        {
            TRACE("");
            for (auto& pair : linker.m_linksForIdMap)
            {
                auto& ownedPairs = m_linksForIdMap[pair.first].m_pairs;
                for (auto& item : ownedPairs )
                {
                    ownedPairs.insert(std::move(item));
                }
            }
        }
    }
}
