#pragma once
#include "ObjectManager.h"
#include "Engine.h"
class Scene
{
public:
	Scene(const std::string& name = "Scene");
	virtual ~Scene();

	//场景生命周期函数
	virtual void OnAttach() {}
	virtual void Reset() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(Engine::TimeStep ts) {}
	virtual void OnRender() {}
	virtual void OnImGuiRender() {}
	

protected:
	std::string m_DebugName;
	ObjectManager m_ObjectManager;
};


class SceneStack
{
public:
	SceneStack();
	~SceneStack();

	void PushScene(Scene* scene);
	void PushOverScene(Scene* overScene);
	void PopScene(Scene* scene);
	void PopOverScene(Scene* overScene);

	std::vector<Scene*>::iterator begin() { return m_Scenes.begin(); }
	std::vector<Scene*>::iterator end() { return m_Scenes.end(); }
private:
	std::vector<Scene*> m_Scenes;
	unsigned int m_SceneInsertIndex = 0;
};