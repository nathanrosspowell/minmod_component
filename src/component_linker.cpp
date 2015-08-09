#include "component_linker.h"
// minmod
#include "component_interface.h"

namespace minmod
{
    namespace component
    {
        Linker::Linker() : m_currentlyLinking(0) {}

        void Linker::Link( Interface* interfacePtr)
        {
            m_currentlyLinking = interfacePtr->GetId();
            interfacePtr->MakeLinks(*this);
            m_currentlyLinking = 0;
        }

        void Linker::Add( Interface* interfacePtr) const
        {
            auto it = m_onAddMap.find(interfacePtr->GetId());
            if ( it != m_onAddMap.end() )
            {
                std::get<AddFunc>(it->second)(interfacePtr);
            }
        }

        void Linker::Remove( Interface* interfacePtr ) const
        {
            auto it = m_onRemoveMap.find(interfacePtr->GetId());
            if ( it != m_onRemoveMap.end() )
            {
                std::get<RemoveFunc>(it->second)();
            }
        }
    }
}
