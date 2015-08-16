#include "component_factory.h"
// stl
#include <cassert>

namespace minmod
{
    namespace component
    {
        void Factory::Insert(Id id, std::string name, CreateFunction createFunc)
        {
            TRACE("Component: " << id << ", " << name);
            m_stringMap.insert(std::make_pair(name, id));
            m_map.insert(std::make_pair(id, createFunc));
        }

        void Factory::Erase(Id id, std::string name)
        {
            TRACE("Component: " << id << ", " << name);
            assert(m_stringMap[name] == id);
            m_stringMap.erase(name);
            m_map.erase(id);
        }

        UniquePtr Factory::Create(Id id)
        {
            auto it = m_map.find(id);
            assert(it != m_map.end());
            return std::move(it->second());
        }

        UniquePtr Factory::Create(std::string name)
        {
            auto it = m_stringMap.find(name);
            assert(it != m_stringMap.end());
            return std::move(Create(it->second));
        }

        Id Factory::GetId(std::string name)
        {
            auto it = m_stringMap.find(name);
            assert(it != m_stringMap.end());
            return it->second;
        }
    }
}
