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
	//对象初始化函数
	virtual void Init() {};

	//对象事件函数
	//用于对象被唤醒时
	virtual void Awake() { m_IsAwake = true;m_IsRender = true; };
	//用于对象被触发时
	virtual void Trigger() {};
	//用于对象被启用时
	virtual void Enable() {};
	//用于对象被禁用时
	virtual void DisEnable() {};
	//用于对象变化阶段时
	virtual void Change() {};
	//用于对象被重置时
	virtual void Reset() {};
	//用于对象被毁灭时
	virtual void Destroy(){ m_IsAwake = false;m_IsRender = true; };


	//更新函数
	//基于时间的更新
	virtual void Update(float ts) {};
	//基于节拍器的更新
	virtual void OnBeat() {};

	//对象渲染函数
	//内部帧缓冲渲染
	virtual void BufferRender() {};
	//实际输出渲染
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

