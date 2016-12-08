#include "component_manager.h"
// stl
#include <utility>
#include <fstream>
#include <cassert>
// json
#include "json11.hpp"
// minmod
#include "component_factory.h"
#include "component_types.h"
#include "component_interface.h"
// Debug
#include <iostream>

namespace minmod
{
    namespace component
    {
        Manager::Manager(Factory& factory) : m_factory(factory)
        {
        }

        void Manager::Deserialize(const json11::Json& json)
        {
            TRACE("Deserialize " << json.dump());
            const auto& entries = json["entries"].array_items();
            for (const auto& entry : entries)
            {
                const auto& name = entry["name"];
                assert(name.is_number());
                Id id = (Id)name.int_value();
                const auto& components = entry["components"];
                assert(components.is_array());
                Insert(id, components);
            }
        }

        json11::Json Manager::Serialize() const
        {
            using namespace json11;
            Json::array entriesArray;
            for (const auto& entryPair : m_entryMap)
            {
                Json::array componentArray;
                const auto& componentMap = entryPair.second->m_componentMap;
                for (const auto& componentPair : componentMap)
                {
                    const auto component = componentPair.second.get();
                    componentArray.push_back(std::move(Json::object({
                        {"name", component->GetName()}, {"data", component->Serialize()},
                    })));
                }
                entriesArray.push_back(std::move(Json::object({
                    {"name", (std::int32_t)entryPair.first}, {"components", componentArray},
                })));
            }
            return Json::object({
                {"name", "Manager"}, {"entries", entriesArray},
            });
        }

        const Interface* Manager::Get(const OwnerId ownerId, const Id componentId) const
        {
            const auto ownerIt = m_entryMap.find(ownerId);
            if (ownerIt != m_entryMap.cend())
            {
                const auto& componentMap = ownerIt->second->m_componentMap;
                const auto compIt = componentMap.find(componentId);
                if (compIt != componentMap.cend())
                {
                    return compIt->second.get();
                }
            }
            return nullptr;
        }

        Interface* Manager::Get(const OwnerId ownerId, const Id componentId)
        {
            return const_cast<Interface*>(static_cast<const Manager*>(this)->Get(ownerId, componentId));
        }

        const Interface* Manager::Get(const OwnerId ownerId, const Name& componentName) const
        {
            const Id id = m_factory.GetId(componentName);
            if (id != INVALID_ID)
            {
                return Get(ownerId, id);
            }
            return nullptr;
        }

        Interface* Manager::Get(const OwnerId ownerId, const Name& componentName)
        {
            return const_cast<Interface*>(static_cast<const Manager*>(this)->Get(ownerId, componentName));
        }

        void Manager::Erase(const OwnerId ownerId)
        {
            TRACE("For ownerId: " << ownerId);
            const auto& entryIt = m_entryMap.find(ownerId);
            if (entryIt != m_entryMap.end())
            {
                EraseList eraseList;
                const auto& componentMap = entryIt->second->m_componentMap;
                for (const auto& component : componentMap)
                {
                    eraseList.push_back(component.first);
                }
                Erase(ownerId, eraseList);
                m_entryMap.erase(entryIt);
            }
        }

        void Manager::Erase(const OwnerId ownerId, const EraseList& eraseList)
        {
            TRACE("For ownerId: " << ownerId << ". " << eraseList.size() << " to remove");
            assert(ownerId != INVALID_ID);
            auto it = m_entryMap.find(ownerId);
            assert(it != m_entryMap.end());
            auto& entry = *(it->second.get());
            for (const auto& removeId : eraseList)
            {
                const auto& linkPair = entry.m_componentMap.find(removeId);
                assert(linkPair != entry.m_componentMap.end());
                TRACE("Removing: " << removeId << " from " << ownerId);
                entry.m_componentMap.erase(linkPair);
            }
        }

        OwnerId Manager::Insert(const OwnerId ownerId, const char* const filePath)
        {
            TRACE("For ownerId: " << ownerId << ". From filePath: " << filePath);
            assert(ownerId != INVALID_ID);
            std::ifstream in(filePath);
            std::string file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            std::string err;
            json11::Json fileJson = json11::Json::parse(file, err);
            auto& jsonComponentMap = fileJson["components"];
            assert(jsonComponentMap.is_array());
            assert(jsonComponentMap.array_items().size() > 0);
            return Insert(ownerId, std::move(jsonComponentMap));
        }

        OwnerId Manager::Insert(const OwnerId ownerId, const json11::Json& json)
        {
            TRACE("For ownerId: " << ownerId << ". From JSON: " << json.dump());
            ComponentMap componentMap;
            for (const auto& jsonComponent : json.array_items())
            {
                auto name = jsonComponent["name"];
                assert(name.is_string());
                auto component = m_factory.Create(name.string_value());
                if (component)
                {
                    auto& data = jsonComponent["data"];
                    assert(data.is_object());
                    component->Deserialize(data);
                    TRACE("  Deserialize of: " << component->GetName());
                    TRACE("    " << component->Serialize().dump());
                    componentMap[component->GetId()] = std::move(component);
                }
            }
            return Insert(ownerId, std::move(componentMap));
        }

        OwnerId Manager::Insert(const OwnerId ownerId, const InsertList& insertList)
        {
            TRACE("For ownerId: " << ownerId << ". " << insertList.size() << " to insert");
            assert(ownerId != INVALID_ID);
            assert(insertList.size() > 0);
            ComponentMap componentMap;
            for (const auto& linkPair : insertList)
            {
                auto component = m_factory.Create(linkPair.first);
                if (component)
                {
                    assert(component->GetId() == linkPair.first);
                    assert(m_factory.GetId(component->GetName()) == linkPair.first);
                    component->Deserialize(linkPair.second);
                    TRACE("  Deserialize of: " << component->GetName());
                    TRACE("    " << component->Serialize().dump());
                    componentMap[component->GetId()] = std::move(component);
                }
            }
            return Insert(ownerId, std::move(componentMap));
        }

        OwnerId Manager::Insert(const OwnerId ownerId, ComponentMap&& componentMap)
        {
            assert(ownerId != INVALID_ID);
            assert(componentMap.size() > 0);
            auto& entry = GetOrCreateEntry(ownerId);
            // Call create on the new components now they are linked.
            for (auto& pair : componentMap)
            {
                pair.second->Create();
            }
            // Insert the new components.
            for (auto& pair : componentMap)
            {
                assert(entry.m_componentMap.find(pair.first) == entry.m_componentMap.end());
                entry.m_componentMap[pair.first] = std::move(pair.second);
            }
            return ownerId;
        }

        auto Manager::GetOrCreateEntry(OwnerId ownerId) -> Entry&
        {
            auto it = m_entryMap.find(ownerId);
            if (it == m_entryMap.end())
            {
                auto pair = m_entryMap.insert(std::make_pair(ownerId, std::make_unique<Entry>()));
                assert(pair.second == true);
                it = pair.first;
            }
            return *(it->second.get());
        }

        void Manager::SetReady(Id componentId)
        {
            TRACE(componentId);
        }

        void Manager::SetNotReady(Id componentId)
        {
            TRACE(componentId);
        }
    }
}
