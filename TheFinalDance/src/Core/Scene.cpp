#include "Scene.h"

Scene::Scene(const std::string& name)
	:m_DebugName(name)
{
}

Scene::~Scene()
{
}

SceneStack::SceneStack()
{
}

SceneStack::~SceneStack()
{
	for (Scene* scene : m_Scenes)
		delete scene;
}

void SceneStack::PushScene(Scene* scene)
{
	m_Scenes.emplace(m_Scenes.begin() + m_SceneInsertIndex, scene);
	++m_SceneInsertIndex;
}

void SceneStack::PushOverScene(Scene* overScene)
{
	m_Scenes.emplace_back(overScene);
}

void SceneStack::PopScene(Scene* scene)
{
	auto it = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
	if (it != m_Scenes.end())
	{
		m_Scenes.erase(it);
		--m_SceneInsertIndex;
	}
}

void SceneStack::PopOverScene(Scene* overScene)
{
	auto it = std::find(m_Scenes.begin(), m_Scenes.end(), overScene);
	if (it != m_Scenes.end())
		m_Scenes.erase(it);
}

