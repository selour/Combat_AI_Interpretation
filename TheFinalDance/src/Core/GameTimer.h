#pragma once
#include "GameEvent.h"
class GameTimer
{
public:
	GameTimer()
	{
	}
	float GetProportion() const
	{
		if (m_StartupFlag && !m_TimeOutFlag)
		{
			return m_Time / m_TimeSet;
		}
		else
		{
			return 1.0f;
		}

	}
	void SetTime(float delayTime)
	{
		m_Time = 0;
		m_TimeSet = delayTime;
		m_StartupFlag = true;
		m_TimeOutFlag = false;
	}

	void Clear()
	{
		m_Time = 0;
		m_TimeSet = 0;
		m_StartupFlag = false;
		m_TimeOutFlag = false;
	}
	void Update(float ts)
	{

		if (m_StartupFlag)
		{
			if (m_TimeOutFlag)
			{
				Clear();
			}
			else
			{
				m_Time += ts;
				if (m_Time >= m_TimeSet)
				{
					m_TimeOutFlag = true;
				}
			}

		}
	}
	bool IsTimeOut() const { return m_TimeOutFlag; }
	operator bool() const { return m_StartupFlag; }
	operator float() const { return GetProportion(); }

private:
	float m_Time = 0;
	float m_TimeSet = 0;
	bool m_StartupFlag = false;
	bool m_TimeOutFlag = false;

};
struct TimePoint
{
	float Time = 0;
	GameEvent<void()> Event;
	TimePoint(float time)
	{
		Time = time;
	}
};
class GameTimeline
{
public:
	TimePoint* Add(float time)
	{
		ENGINE_ASSERT(m_EndTime >= time, "The time point inserted after must be greater than the previous time point!")
		m_EndTime = time;
		m_TimeLine.push_back(TimePoint(time));
		return &m_TimeLine.back();
	}
	TimePoint* Get(int index)
	{
		return &m_TimeLine[index];
	}
	void Clear()
	{
		m_Time = 0;
		m_EndTime = 0;
		m_StartupFlag = false;
		m_TimeOutFlag = false;
		m_TimeLine.clear();
	}
	void Update(float ts)
	{

		if (m_StartupFlag)
		{
			m_Time += ts;
			while (!m_TimeLine.empty() && m_TimeLine.size() > m_CurrentIndex && m_TimeLine[m_CurrentIndex].Time >= m_Time)
			{
				m_TimeLine[m_CurrentIndex].Event();
				m_CurrentIndex++;
			}
			if (m_TimeLine.empty() || m_TimeLine.size() <= m_CurrentIndex)
			{
				m_StartupFlag = false;
				m_TimeOutFlag = true;
			}
		}
		else
		{
			if (m_TimeOutFlag)
				m_TimeOutFlag = false;
		}
	}
	bool IsTimeOut() const { return m_TimeOutFlag; }
	operator bool() const { return m_StartupFlag; }
private:
	float m_EndTime = 0;
	float m_Time = 0;
	int m_CurrentIndex = 0;
	bool m_StartupFlag = false;
	bool m_TimeOutFlag = false;
	std::vector<TimePoint> m_TimeLine;
};