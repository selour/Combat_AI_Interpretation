#pragma once
#include <glm/glm.hpp>
#include "Delay.h"
#include "Engine.h"
class Object
{
public:
	virtual ~Object() = 0;
	//对象周期函数
	virtual void Start() = 0;
	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;
	virtual void Destroy() = 0;

	bool IsAwake() const
	{
		return m_IsAwake;
	}
	bool IsRender() const
	{
		return m_IsRender;
	}
private:
	bool m_IsAwake = false;
	bool m_IsRender = false;

};

class BattlePlayer
{
public:
	enum MoveMode
	{
		None = 0, X = 1, Y = 2, ErrorX = 3, ErrorY = 4
	};


	BattlePlayer(glm::vec2 pos);

	void Move(MoveMode moveMode, float direction, float time);
	
	const glm::vec2 GetPos() const;
	const bool IsMove() const;
	const bool IsInteractive() const;

	void Update(float ts);
	
private:
	MoveMode m_MoveMode;
	float m_PosX, m_PosY;
	DelaySwitch m_IsMove;
	DelaySwitch m_IsInteractive;
	float m_Current;
	float m_Direction;
	
};

