#pragma once
#include <glm/glm.hpp>
#include "Engine.h"
#include "ResourceManager.h"
#include <unordered_map>
#include <memory>

class EventQueue;

class Object
{
public:
	virtual ~Object() {};
	//�����ʼ������
	virtual void Init() {};

	//�����¼�����
	//���ڶ��󱻻���ʱ
	virtual void Awake() { m_IsAwake = true;m_IsRender = true; };
	//���ڶ��󱻴���ʱ
	virtual void Trigger() {};
	//���ڶ�������ʱ
	virtual void Enable() {};
	//���ڶ��󱻽���ʱ
	virtual void DisEnable() {};
	//���ڶ���仯�׶�ʱ
	virtual void Change() {};
	//���ڶ�������ʱ
	virtual void Reset() {};
	//���ڶ��󱻻���ʱ
	virtual void Destroy(){ m_IsAwake = false;m_IsRender = true; };


	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) {};
	//���ڽ������ĸ���
	virtual void OnBeat() {};

	//������Ⱦ����
	//�ڲ�֡������Ⱦ
	virtual void BufferRender() {};
	//ʵ�������Ⱦ
	virtual void Render() {};


	bool IsAwake() const
	{
		return m_IsAwake;
	}
	bool IsRender() const
	{
		return m_IsRender;
	}
protected:
	bool m_IsAwake = false;
	bool m_IsRender = false;

};

class GameObject : public Object
{
public:
	void SetEventQueue(EventQueue* eventQueue)
	{
		m_EventQueue = eventQueue;
	}
	void SetResourceManager(ResourceManager* resourceManager)
	{
		m_ResourceManager = resourceManager;
	}
	void SetParticleSystem(Engine::ParticleSystem* particleSystem)
	{
		m_ParticleSystem = particleSystem;
	}
protected:
	EventQueue* m_EventQueue = nullptr;

	ResourceManager* m_ResourceManager = nullptr;

	Engine::ParticleSystem* m_ParticleSystem = nullptr;
};
class ObjectManager
{
public:
	void Add(const std::string& name, const std::shared_ptr<GameObject>& object);
	std::shared_ptr<GameObject> Get(const std::string& name);
	bool IsExists(const std::string& name) const;

	void AllObjectInit();
	void AllObjectUpdate(float ts);
	void AllObjectBufferRender();
	void AllObjectOnBeat();
	
	void AllObjectSetEventQueue(EventQueue* eventQueue);
	void AllObjectSetResourceManager(ResourceManager* resourceManager);
	void AllObjectSetParticleSystem(Engine::ParticleSystem* particleSystem);

private:
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_Objects;
};

