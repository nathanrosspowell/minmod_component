#include "component_factory.h"
// stl
#include <cassert>

namespace minmod
{
    namespace component
    {
        void Factory::Insert(const Id id, const Name& name, CreateFunction createFunc)
        {
            TRACE("Component: " << id << ", " << name);
            m_stringMap.insert(std::make_pair(name, id));
            m_map.insert(std::make_pair(id, std::move(createFunc)));
        }

        void Factory::Erase(const Id id, const Name& name)
        {
            TRACE("Component: " << id << ", " << name);
            assert(m_stringMap.find(name) != m_stringMap.end());
            assert(m_stringMap[name] == id);
            m_stringMap.erase(name);
            m_map.erase(id);
        }

        UniquePtr Factory::Create(const Id id)
        {
            auto it = m_map.find(id);
            assert(it != m_map.end());
            return std::move(it->second());
        }

        UniquePtr Factory::Create(const Name& name)
        {
            return std::move(Create(GetId(name)));
        }

        Id Factory::GetId(const Name& name)
        {
            auto it = m_stringMap.find(name);
            assert(it != m_stringMap.end());
            return it->second;
        }
    }
}
