#include "component_linker.h"
// minmod
#include "component_interface.h"

namespace minmod
{
    namespace component
    {
        void Linker::AddComponent( Interface* interfacePtr) const
        {
            auto it = m_onAddMap.find(interfacePtr->GetId());
            if ( it != m_onAddMap.end() )
            {
                it->second(interfacePtr);
            }
        }

        void Linker::RemoveComponent( Interface* interfacePtr ) const
        {
            auto it = m_onRemoveMap.find(interfacePtr->GetId());
            if ( it != m_onRemoveMap.end() )
            {
                it->second();
            }
        }

        void Linker::UnLink( Id /*id*/ )
        {
        }

        void Linker::MoveLinks( Linker&& linker )
        {
            m_onAddMap.insert( linker.m_onAddMap.begin(), linker.m_onAddMap.end());
            m_onRemoveMap.insert( linker.m_onRemoveMap.begin(), linker.m_onRemoveMap.end());
        }
    }
}
