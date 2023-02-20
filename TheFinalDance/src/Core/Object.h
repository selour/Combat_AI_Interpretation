#pragma once
#include <glm/glm.hpp>
#include "Delay.h"
class BattlePlayer
{
public:
	BattlePlayer(glm::vec2 pos);
	void MoveX(float direction, float time);
	void MoveY(float direction, float time);

	const glm::vec2 GetPos() const;
	const bool IsMove() const;
	const bool IsInteractive() const;

	void Update(float ts);
private:
	
	float m_PosX, m_PosY;
	DelaySwitch m_IsMoveX;
	DelaySwitch m_IsMoveY;
	DelaySwitch m_IsInteractive;
	float m_Current;
	float m_Direction;
	
};

