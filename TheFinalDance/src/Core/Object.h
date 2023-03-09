#pragma once
#include <glm/glm.hpp>
#include "Delay.h"
#include "Engine.h"
class Object
{
public:
	virtual ~Object() {};
	//对象周期函数
	virtual void Start() = 0;
	virtual void Awake() = 0;
	virtual void Reset() = 0;
	virtual void Destroy() = 0;

	virtual void Update(float ts) = 0;

	virtual void OnBeat() = 0;

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


