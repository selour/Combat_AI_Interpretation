#pragma once
#include <glm/glm.hpp>
#include "Engine.h"
#include <unordered_map>
#include <memory>
class Object
{
public:
	virtual ~Object() {};
	//对象初始化函数
	virtual void Start() = 0;

	//对象周期函数
	virtual void Awake() = 0;
	virtual void Reset() = 0;
	virtual void Destroy() = 0;

	virtual void Update(float ts) = 0;
	virtual void OnBeat() = 0;

	//对象渲染函数
	virtual void BufferRender() = 0;
	virtual void Render() = 0;


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
class ObjectManager
{
public:
	void Add(const std::string& name, const std::shared_ptr<Object>& object);
	std::shared_ptr<Object> Get(const std::string& name);
	bool IsExists(const std::string& name) const;

	void AllObjectStart();
	void AllObjectUpdate(float ts);
	void AllObjectBufferRender();
	void AllObjectOnBeat();
private:
	std::unordered_map<std::string, std::shared_ptr<Object>> m_Objects;
};

