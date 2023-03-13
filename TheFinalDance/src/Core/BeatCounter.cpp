#include "BeatCounter.h"

//------------------½ÚÅÄ¼ÆËãÆ÷---------------------
BeatCounter::BeatCounter(ObjectManager* objects)
	:m_Bpm(100),m_Time(0), m_Objects(objects)
{
}

void BeatCounter::Reset()
{
	m_Time = 0;
}

void BeatCounter::Update(float ts)
{
	if (m_IsAwake)
	{
		float bv = 60.0f / (float)m_Bpm;
		m_Time += ts;
		if (m_Time >= bv)
		{
			m_Objects->AllObjectOnBeat();
			m_Time -= bv;
		}
	}
	
	
}

