#include "component_linker.h"
// minmod
#include "component_interface.h"

namespace minmod
{
    namespace Component
    {
        void Linker::Add( Interface* interfacePtr) const
        {
            auto it = m_onAddMap.find(interfacePtr->GetId());
            if ( it != m_onAddMap.end() )
            {
                it->second(interfacePtr);
            }
        }

        void Linker::Remove( Interface* interfacePtr ) const
        {
            auto it = m_onRemoveMap.find(interfacePtr->GetId());
            if ( it != m_onRemoveMap.end() )
            {
                it->second();
            }
        }
    }
}
