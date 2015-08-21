// minmod
#include "component_registrant.h"
#include "component_factory.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        CustomRegistrant::CustomRegistrant(Id id, std::string name, Func func) : m_id(id), m_name(name)
        {
            Factory::GetInstance().Insert(m_id, m_name, [func, this]()
                                          {
                                              return func(m_id, m_name);
                                          });
        }
        CustomRegistrant::~CustomRegistrant()
        {
            Factory::GetInstance().Erase(m_id, m_name);
        }
    }
}