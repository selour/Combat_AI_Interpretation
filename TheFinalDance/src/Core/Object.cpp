#include "Object.h"

BattlePlayer::BattlePlayer(glm::vec2 pos)
	:m_PosX(pos.x),m_PosY(pos.y), m_Current(0), m_Direction(0)
{
}



void BattlePlayer::MoveX(float direction, float time)
{
	m_IsMoveX.SetDelay(time);
	
	m_Current = m_PosX;
	m_Direction = direction;
}
void BattlePlayer::MoveY(float direction, float time)
{
	m_IsMoveY.SetDelay(time);

	m_Current = m_PosY;
	m_Direction = direction;
}

const glm::vec2 BattlePlayer::GetPos() const
{
	return glm::vec2(m_PosX, m_PosY);
}

const bool BattlePlayer::IsMove() const
{
	return m_IsMoveX || m_IsMoveY;
}

const bool BattlePlayer::IsInteractive() const
{
	return m_IsInteractive;
}

void BattlePlayer::Update(float ts)
{
	m_IsMoveX.Update(ts);
	m_IsMoveY.Update(ts);
	m_IsInteractive.Update(ts);
	if (IsMove())
	{
		if(m_IsMoveX)
			m_PosX = m_Current + m_Direction * m_IsMoveX.GetProportion();
		else
			m_PosY = m_Current + m_Direction * m_IsMoveY.GetProportion();
	}
	
}
