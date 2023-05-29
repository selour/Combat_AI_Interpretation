#include "ObjectManager.h"
//----------------------游戏对象列表-----------------------------
void ObjectList::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->Init();
}

void ObjectList::SetPost(const std::shared_ptr<PostObject>& object)
{
	m_Post = object;
}

void ObjectList::SetCamera(const std::shared_ptr<Engine::Camera>& camera)
{
	m_Camera = camera;
}


void ObjectList::Update(float ts)
{
	for (auto& object : m_Objects)
	{
		object->Update(ts);
	}
}

void ObjectList::Render()
{
	if (m_Post)
	{
		m_Post->Bind();
		if (m_Camera)
			m_Camera->ViewportActivated();
		for (auto& object : m_Objects)
		{
			object->Render(m_Camera);
		}
		m_Post->UnBind();
	}
	else
	{
		if (m_Camera)
			m_Camera->ViewportActivated();
		for (auto& object : m_Objects)
		{
			object->Render(m_Camera);
		}
	}
	
}

void ObjectList::OnImGuiRender()
{
	for (auto& object : m_Objects)
	{
		object->OnImGuiRender();
	}
}






//----------------------游戏对象管理器-----------------------------
void ObjectManager::Reset(int max)
{
	m_MaxIndex = max;
	m_ObjectLayers.resize(max);
}
void ObjectManager::Add(int index, const std::shared_ptr<GameObject>& object)
{
	ENGINE_ASSERT(!IsOverflow(index), "Index overflow！");
	object->SetObjectManager(this);
	m_ObjectLayers[index].Add(object);
	
	
}

void ObjectManager::AddLogic(const std::shared_ptr<GameObject>& object)
{
	object->SetObjectManager(this);
	object->Init();
	m_LogicObjects.push_back(object);
}

void ObjectManager::SetPost(int index, const std::shared_ptr<PostObject>& object)
{
	ENGINE_ASSERT(!IsOverflow(index), "Index overflow！");
	m_ObjectLayers[index].SetPost(object);
}

void ObjectManager::SetCamera(int index, const std::shared_ptr<Engine::Camera>& camera)
{
	ENGINE_ASSERT(!IsOverflow(index), "Index overflow！");
	m_ObjectLayers[index].SetCamera(camera);
}

bool ObjectManager::IsOverflow(int index) const
{
	return m_ObjectLayers.empty() || m_MaxIndex <= index || index < 0;
}


void ObjectManager::Update(float ts)
{
	for (auto& object : m_LogicObjects)
	{
		object->Update(ts);
	}
	for (auto& object : m_ObjectLayers)
	{
		object.Update(ts);
	}
}


void ObjectManager::Render()
{
	for (auto& object : m_ObjectLayers)
	{
		object.Render();
	}
}

void ObjectManager::OnImGuiRender()
{
	for (auto& object : m_LogicObjects)
	{
		object->OnImGuiRender();
	}
	for (auto& object : m_ObjectLayers)
	{
		object.OnImGuiRender();
	}
}

