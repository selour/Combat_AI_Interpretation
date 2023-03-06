#include "BeatCounter.h"


BeatCounter::BeatCounter()
	:m_Bpm(100),m_Time(0),m_BeatCounter(0)
{
}

void BeatCounter::Clear()
{
	m_Time = 0;
	m_BeatCounter = 0;
}

void BeatCounter::Update(float ts)
{
	float bv = 60.0f / (float)m_Bpm;
	m_Time += ts;
	if (m_Time >= bv)
	{
		for (int i = 0; i < m_Objects.size(); i++)
		{
			m_Objects[i]->OnBeat();
		}
		m_BeatCounter++;
		m_Time -= bv;
	}
	
}
