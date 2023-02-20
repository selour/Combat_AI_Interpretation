#include "BeatCounter.h"


BeatCounter::BeatCounter(std::shared_ptr<Timeline> timeline)
	:m_Bpm(100),m_Time(0),m_BeatCounter(0),m_Timeline(timeline)
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
		m_Timeline->BeatUpdate();
		m_BeatCounter++;
		m_Time -= bv;
	}
	
}
