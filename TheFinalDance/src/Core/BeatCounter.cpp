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

void BeatCounter::Update(Engine::TimeStep ts)
{
	float bv = 60.0f / (float)m_Bpm;
	m_Time += ts;
	if (m_Time >= bv)
	{
		m_BeatCounter++;
		m_Time -= bv;
	}
	
}
