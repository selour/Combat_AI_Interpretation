#pragma once
#include <glm/glm.hpp>
#include "Delay.h"

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

