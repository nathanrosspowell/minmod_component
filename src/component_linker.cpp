#include "component_linker.h"
// stl
#include <algorithm>
// minmod
#include "component_interface.h"
// Debug
#include <iostream> 
using std::cout;
using std::endl;

namespace minmod
{
    namespace component
    {
        Linker::~Linker()
        {
            TRACE("Clean up Linker");
            std::vector<Id> toRemove;
            std::for_each(m_onAddMap.cbegin(), m_onAddMap.cend(),
                [&toRemove](const auto& pair)
                {
                    toRemove.push_back(pair.first);
                }
            );
            std::for_each(toRemove.cbegin(), toRemove.cend(),
                [this](Id id)
                {
                    RemoveComponent(id);
                }
            );
            std::for_each(toRemove.cbegin(), toRemove.cend(),
                [this](Id id)
                {
                    UnLink(id);
                }
            );
        }

        void Linker::Link( Interface* interfacePtr)
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: "<<interfacePtr->GetName()<<", Id: "<<interfacePtr->GetId());
            m_currentlyLinking = interfacePtr->GetId();
            interfacePtr->MakeLinks(*this);
            m_currentlyLinking = 0;
        }

        void Linker::UnLink( Id id )
        {
            assert(id != INVALID_ID);
            TRACE("Id: "<<id);
            for (auto& addMap : m_onAddMap)
            {
                addMap.second.erase(id);
            }
            for (auto& removeMap : m_onRemoveMap)
            {
                removeMap.second.erase(id);
            }
        }

        void Linker::AddComponent( Interface* interfacePtr) const
        {
            assert(interfacePtr != nullptr);
            TRACE("Name: "<<interfacePtr->GetName()<<", Id: "<<interfacePtr->GetId());
            auto it = m_onAddMap.find(interfacePtr->GetId());
            if ( it != m_onAddMap.end() )
            {
                for ( const auto& pair : it->second )
                {
                    pair.second(interfacePtr);
                }
            }
        }

        void Linker::RemoveComponent( Id id )
        {
            TRACE("Id: "<<id);
            assert(id != INVALID_ID);
            auto it = m_onRemoveMap.find(id);
            // Remove everything that linked against this component.
            if ( it != m_onRemoveMap.end() )
            {
                for ( const auto& pair : it->second )
                {
                    pair.second();
                }
            }
            // Unlink anything this component linked against.
            for ( const auto& map : m_onRemoveMap)
            {
                for ( const auto& pair : map.second )
                {
                    if ( pair.first == id )
                    {
                        pair.second();
                    }
                }
            }
        }

        void Linker::MoveLinks( Linker&& linker )
        {
            TRACE("");
            m_onAddMap.insert( linker.m_onAddMap.begin(), linker.m_onAddMap.end());
            m_onRemoveMap.insert( linker.m_onRemoveMap.begin(), linker.m_onRemoveMap.end());
        }
    }
}
