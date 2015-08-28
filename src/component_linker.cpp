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
        Linker::~Linker()
        {
            TRACE("Clean up Linker");
            std::vector<Id> toRemove;
            for (const auto& pair : m_entryMap)
            {
                toRemove.push_back(pair.first);
                RemoveComponent(pair.first);
            }
            for (const auto& id : toRemove)
            {
                UnLink(id);
            }
        }

        void Linker::Link(Interface* const interfacePtr)
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: " << interfacePtr->GetName() << ", Id: " << interfacePtr->GetId());
            m_currentlyLinking = interfacePtr->GetId();
            interfacePtr->MakeLinks(*this);
            m_currentlyLinking = INVALID_ID;
        }

        void Linker::UnLink(const Id id)
        {
            assert(id != INVALID_ID);
            TRACE("Id: " << id);
            for (auto& pair : m_entryMap)
            {
                pair.second.erase(id);
            }
        }

        void Linker::AddComponent(Interface* const interfacePtr) const
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: " << interfacePtr->GetName() << ", Id: " << interfacePtr->GetId());
            auto it = m_entryMap.find(interfacePtr->GetId());
            if (it != m_entryMap.end())
            {
                for (const auto& ownedPair : it->second)
                {
                    auto& addFun = ownedPair.second.first;
                    addFun(interfacePtr);
                }
            }
        }

        void Linker::RemoveComponent(const Id id)
        {
            TRACE("Id: " << id);
            assert(id != INVALID_ID);
            auto it = m_entryMap.find(id);
            if (it != m_entryMap.end())
            {
                for (const auto& funcPair : it->second)
                {
                    auto& removeFunc = funcPair.second.second;
                    removeFunc();
                }
            }
            // Unlink anything this component linked against.
            for (const auto& pair : m_entryMap)
            {
                for (const auto& ownedPair : pair.second)
                {
                    if (ownedPair.first == id)
                    {
                        auto& removeFunc = ownedPair.second.second;
                        removeFunc();
                    }
                }
            }
        }

        void Linker::MoveLinks(const Linker&& linker)
        {
            TRACE("");
            for (auto& pair : linker.m_entryMap)
            {
                auto& ownedPairs = m_entryMap[pair.first];
                ownedPairs.insert(pair.second.begin(), pair.second.end());
            }
        }
    }
}
