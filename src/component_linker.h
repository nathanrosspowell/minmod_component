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
            template< class COMPONENT >
            void Link(std::function<void(COMPONENT*)> add, std::function<void()> remove )
            {
                assert(m_currentlyLinking != INVALID_ID);
                auto& ownedPairs = m_entryMap[COMPONENT::GetStaticId()];
                ownedPairs[m_currentlyLinking] = std::make_pair(
                    [add](Interface* ptr) 
                    { 
                        assert(dynamic_cast<COMPONENT*>(ptr) != nullptr);
                        add(static_cast<COMPONENT*>(ptr));
                    },
                    remove );
            }

        private:
            using AddFunc = std::function<void(Interface*)>;
            using RemoveFunc = std::function<void()>;
            using AddMap = std::unordered_map< Id, AddFunc >;
            using RemoveMap = std::unordered_map< Id, RemoveFunc >;
            using FuncPair = std::pair<AddFunc, RemoveFunc>;
            using OwnedPairs = std::unordered_map<Id, FuncPair>;
            using EntryMap = std::unordered_map< Id, OwnedPairs>;

        private:
            friend class Manager;
            void Link( Interface* interfacePtr);
            void UnLink( Id id );
            void AddComponent( Interface* interfacePtr) const;
            void RemoveComponent( Id id);
            void MoveLinks( Linker&& linker );

        private:
            EntryMap m_entryMap;
            Id m_currentlyLinking = INVALID_ID;
        };
    }
}
