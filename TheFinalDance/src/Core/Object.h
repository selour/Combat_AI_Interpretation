#pragma once
#include "Engine.h"
class ObjectManager;

class GameObject
{
public:
	virtual ~GameObject() {};
	//对象初始化函数
	virtual void Init() {};
	//更新函数
	//基于时间的更新
	virtual void Update(float ts) {};

	//对象渲染函数
	virtual void Render(std::shared_ptr<Engine::Camera> camera) {};
	//调试UI渲染
	virtual void OnImGuiRender() {};

	void SetObjectManager(ObjectManager* objectManager)
	{
		m_ObjectManager = objectManager;
	}
protected:
	ObjectManager* m_ObjectManager;
}; 

class PostObject : public GameObject
{
public:
	virtual ~PostObject() {};

	virtual void Bind() {};
	virtual void UnBind() {};
};