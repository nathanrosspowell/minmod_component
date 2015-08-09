#include "component_linker.h"
// minmod
#include "component_interface.h"

namespace minmod
{
    namespace component
    {
        void Linker::Link( Interface* interfacePtr)
        {
            m_currentlyLinking = interfacePtr->GetId();
            interfacePtr->MakeLinks(*this);
            m_currentlyLinking = 0;
        }

        void Linker::UnLink( Id id )
        {
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
            auto it = m_onAddMap.find(interfacePtr->GetId());
            if ( it != m_onAddMap.end() )
            {
                for ( const auto& pair : it->second )
                {
                    pair.second(interfacePtr);
                }
            }
        }

        void Linker::RemoveComponent( Interface* interfacePtr )
        {
            auto it = m_onRemoveMap.find(interfacePtr->GetId());
            if ( it != m_onRemoveMap.end() )
            {
                for ( const auto& pair : it->second )
                {
                    pair.second();
                }
            }
            UnLink(interfacePtr->GetId());
        }


        void Linker::MoveLinks( Linker&& linker )
        {
            m_onAddMap.insert( linker.m_onAddMap.begin(), linker.m_onAddMap.end());
            m_onRemoveMap.insert( linker.m_onRemoveMap.begin(), linker.m_onRemoveMap.end());
        }
    }
}
