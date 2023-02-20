#include "Object.h"

BattlePlayer::BattlePlayer(glm::vec2 pos)
	:m_MoveMode(MoveMode::None),m_PosX(pos.x),m_PosY(pos.y), m_Current(0), m_Direction(0)
{
}

void BattlePlayer::Move(MoveMode moveMode, float direction, float time)
{
	m_IsMove.SetDelay(time);
	m_MoveMode = moveMode;
	if(m_MoveMode == X || m_MoveMode == ErrorX)
		m_Current = m_PosX;
	else
		m_Current = m_PosY;
	m_Direction = direction;
}


const glm::vec2 BattlePlayer::GetPos() const
{
	return glm::vec2(m_PosX, m_PosY);
}

const bool BattlePlayer::IsMove() const
{
	return m_IsMove;
}

const bool BattlePlayer::IsInteractive() const
{
	return m_IsInteractive;
}

void BattlePlayer::Update(float ts)
{
	m_IsMove.Update(ts);
	m_IsInteractive.Update(ts);
	if (IsMove())
	{
		switch (m_MoveMode)
		{
		case X:m_PosX = m_Current + m_Direction * m_IsMove.GetProportion(); break;
		case Y:m_PosY = m_Current + m_Direction * m_IsMove.GetProportion(); break;
		case ErrorX:m_PosX = m_Current + 0.2 * sin(glm::radians(m_Direction *180.0f * m_IsMove.GetProportion())); break;
		case ErrorY:m_PosY = m_Current + 0.2 * sin(glm::radians(m_Direction * 180.0f * m_IsMove.GetProportion())); break;
		}
		
			
	}
	
}
