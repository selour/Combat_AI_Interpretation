#include "BeatCounter.h"

//------------------节拍计算器---------------------
BeatCounter::BeatCounter()
	:m_Bpm(100),m_Time(0)
{
}

void BeatCounter::Clear()
{
	m_Time = 0;
}

void BeatCounter::Update(float ts)
{
	float bv = 60.0f / (float)m_Bpm;
	m_Time += ts;
	if (m_Time >= bv)
	{
		m_TimeLine.OnBeat();
		for (int i = 0; i < m_Objects.size(); i++)
		{
			m_Objects[i]->OnBeat();
		}
		m_Time -= bv;
	}
	m_TimeLine.Update();
	
}


//------------------时间轴（基于节拍）---------------------

void TimeLine::AddEvent(EventType type, unsigned int beat, unsigned int value)
{
	m_EventList.push_back(BeatEvent(type, beat, value));
}

void TimeLine::Update()
{
	if (m_OnBeat)
	{

		while (m_index < m_EventList.size() && m_BeatCount == m_EventList[m_index].Beat)
		{
			switch (m_EventList[m_index].Type)
			{
			case 0:
				m_Objects[m_EventList[m_index].Value]->Awake();
				break;
			case 1:
				m_Objects[m_EventList[m_index].Value]->Destroy();
				break;
			case 2:
				m_BeatCount = m_EventList[m_index].Value - 1;
				break;
			}
			m_index++;
		}
		m_OnBeat = false;
		m_BeatCount++;
	}
}

void TimeLine::OnBeat()
{
	m_OnBeat = true;
}
