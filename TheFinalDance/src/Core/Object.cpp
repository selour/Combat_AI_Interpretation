#include "Object.h"

void ObjectManager::Add(const std::string& name, const std::shared_ptr<Object>& object)
{
	ENGINE_ASSERT(!IsExists(name), "Object already exists!");
	m_Objects[name] = object;
}

std::shared_ptr<Object> ObjectManager::Get(const std::string& name)
{
	ENGINE_ASSERT(IsExists(name), "Object not found!");
	return m_Objects[name];
}

bool ObjectManager::IsExists(const std::string& name) const
{
	return m_Objects.find(name) != m_Objects.end() && !m_Objects.empty();
}

void ObjectManager::AllObjectStart()
{
	for (auto& [_, object] : m_Objects)
	{
		object->Start();
	}
}

void ObjectManager::AllObjectUpdate(float ts)
{
	for (auto& [_, object] : m_Objects)
	{
		object->Update(ts);
	}
}

void ObjectManager::AllObjectBufferRender()
{
	for (auto& [_, object] : m_Objects)
	{
		object->BufferRender();
	}
}

void ObjectManager::AllObjectOnBeat()
{
	for (auto& [_, object] : m_Objects)
	{
		object->OnBeat();
	}
}
