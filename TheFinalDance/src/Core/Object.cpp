#include "Object.h"
//------------------节拍计算器---------------------
void BeatCounter::Reset(int bpm)
{
	m_Time = 0;
	m_Bpm = bpm;
}

void BeatCounter::Update(float ts)
{

	float bv = 60.0f / (float)m_Bpm;
	
	if (m_Time >= bv || m_Time == 0)
	{
		m_Objects->AllObjectOnBeat();
		if (m_Time >= bv)
			m_Time -= bv;
	}
	m_Time += ts;

}

//----------------------游戏对象管理器-----------------------------
void ObjectManager::Add(const std::string& name, const std::shared_ptr<GameObject>& object)
{
	ENGINE_ASSERT(!IsExists(name), "Object already exists!");
	m_Objects[name] = object;
}

std::shared_ptr<GameObject> ObjectManager::Get(const std::string& name)
{
	ENGINE_ASSERT(IsExists(name), "Object not found!");
	return m_Objects[name];
}

bool ObjectManager::IsExists(const std::string& name) const
{
	return m_Objects.find(name) != m_Objects.end() && !m_Objects.empty();
}


void ObjectManager::AllObjectInit()
{
	for (auto& [_, object] : m_Objects)
	{
		object->Init();
	}
}

void ObjectManager::AllObjectUpdate(float ts)
{
	m_BeatCounter->Update(ts);
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

void ObjectManager::AllObjectSetEventQueue(EventQueue* eventQueue)
{
	for (auto& [_, object] : m_Objects)
	{
		object->SetEventQueue(eventQueue);
	}
}

void ObjectManager::AllObjectSetResourceManager(ResourceManager* resourceManager)
{
	for (auto& [_, object] : m_Objects)
	{
		object->SetResourceManager(resourceManager);
	}
}

void ObjectManager::AllObjectSetParticleSystem(Engine::ParticleSystem* particleSystem)
{
	for (auto& [_, object] : m_Objects)
	{
		object->SetParticleSystem(particleSystem);
	}
}
