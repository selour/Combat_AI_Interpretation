#pragma once
#include "Engine.h"
class ObjectManager;

class GameObject
{
public:
	virtual ~GameObject() {};
	//�����ʼ������
	virtual void Init() {};
	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) {};

	//������Ⱦ����
	virtual void Render(std::shared_ptr<Engine::Camera> camera) {};
	//����UI��Ⱦ
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