// minmod
#include "component_scoped_registrant.h"
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        ScopedRegistrant::ScopedRegistrant(Factory& factory, const Id id, const Name& name, Func&& func) : m_factory(factory), m_id(id), m_name(name)
        {
            m_factory.Insert(m_id, m_name, [func = std::move(func), this]()
                                          {
                                              return func(m_id, m_name);
                                          });
        }

        ScopedRegistrant::~ScopedRegistrant()
        {
            m_factory.Erase(m_id, m_name);
        }
    }
}
