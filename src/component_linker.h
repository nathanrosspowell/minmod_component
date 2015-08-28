#pragma once
// stl
#include <unordered_map>
#include <functional>
#include <cassert>
#include <memory>
// minmod
#include "component_types.h"

namespace minmod
{
    namespace component
    {
        class Interface;
        class Linker
        {
        public:
            ~Linker();
            template <class COMPONENT> void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove)
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

        private:
            using AddFunc = std::function<void(Interface* const)>;
            using RemoveFunc = std::function<void()>;
            using AddMap = std::unordered_map<Id, AddFunc>;
            using RemoveMap = std::unordered_map<Id, RemoveFunc>;
            using FuncPair = std::pair<AddFunc, RemoveFunc>;
            using OwnedPairs = std::unordered_map<Id, FuncPair>;
            using EntryMap = std::unordered_map<Id, OwnedPairs>;

        private:
            friend class Manager;
            void Link(Interface* const interfacePtr);
            void UnLink(const Id id);
            void AddComponent(Interface* const interfacePtr) const;
            void RemoveComponent(const Id id);
            void MoveLinks(const Linker&& linker);

        private:
            EntryMap m_entryMap;
            Id m_currentlyLinking = INVALID_ID;
        };
    }
}
