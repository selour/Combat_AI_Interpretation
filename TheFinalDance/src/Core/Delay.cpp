#include "Delay.h"

DelaySwitch::DelaySwitch()
	:m_Switch(false), m_Time(-1.0f), m_DelayTime(-1.0f)
{
}

void DelaySwitch::SetDelay(float delayTime)
{
	m_Switch = true;
	m_DelayTime = delayTime;
	m_Time = 0;
}

void DelaySwitch::Clear()
{
	m_Switch = false;
	m_Time = -1.0f;
	m_DelayTime = -1.0f;
}

void DelaySwitch::Update(float ts)
{
	if (m_Switch)
	{
		if (m_Time == -1.0f)
		{
			m_Switch = false;
		}
		else
		{
			m_Time += ts;
			if (m_Time >= m_DelayTime)
			{
				m_Time = -1.0f;
				m_DelayTime = -1.0f;
			}
		}
	
	}
}

