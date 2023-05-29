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
	void SetLoop(bool flag)
	{
		m_Loop = flag;
	}

	void Clear()
	{
		m_Time = 0;
		m_TimeSet = 0;
		m_StartupFlag = false;
		m_TimeOutFlag = false;
		m_Loop = false;
	}
	void Update(float ts)
	{

		if (m_StartupFlag)
		{
			if (m_TimeOutFlag)
			{
				if (m_Loop)
				{
					m_TimeOutFlag = false;
					m_Time -= m_TimeSet;
				}
				else
				{
					Clear();
				}
			}
			m_Time += ts;
			if (m_Time >= m_TimeSet)
			{
				m_TimeOutFlag = true;
			}

		}
	}
	bool GetFlag() const { return m_StartupFlag; }
	bool IsTimeOut() const { return m_TimeOutFlag; }
	operator bool() const { return m_StartupFlag; }
	operator float() const { return GetProportion(); }

private:
	float m_Time = 0;
	float m_TimeSet = 0;
	bool m_StartupFlag = false;
	bool m_TimeOutFlag = false;
	bool m_Loop = false;

};
struct TimePoint
{
	float Time = 0;
	bool Flag = false;
	TimePoint(float time)
	{
		Time = time;
	}
};
class GameTimeline
{
	
public:
	GameTimeline()
	{
		Clear();
		m_TimeLine.reserve(3);
	}

	TimePoint* Add(float time)
	{
		m_TimeLine.push_back(TimePoint(time));
		return &m_TimeLine.back();
	}
	void Start()
	{
		m_StartupFlag = true;
	}
	
	void Clear()
	{
		m_Time = 0;
		m_CurrentIndex = 0;
		m_StartupFlag = false;
		m_TimeLine.clear();
	}
	void Update(float ts)
	{

		if (m_StartupFlag)
		{
			m_Time += ts;
			if (!m_TimeLine.empty())
			{
				if (m_TimeLine[m_CurrentIndex].Flag)
				{
					m_TimeLine[m_CurrentIndex].Flag = false;
					m_CurrentIndex++;
					
				}
				if (m_TimeLine.size() <= m_CurrentIndex)
				{
					m_StartupFlag = false;
				}
				else
				{
					if (m_TimeLine[m_CurrentIndex].Time <= m_Time)
					{
						m_TimeLine[m_CurrentIndex].Flag = true;
						m_Time -= m_TimeLine[m_CurrentIndex].Time;
						
					}
				}
				
			}
			else
			{
				m_StartupFlag = false;
			}
			
			
		}
	}
	bool GetFlag()
	{
		
		return m_TimeLine[m_CurrentIndex].Flag;
		
	}
	int GetCurrentIndex()
	{
		return m_CurrentIndex;
	}
	bool GetFlag(int index)
	{
		if (!m_TimeLine.empty() && index >= 0 && index < m_TimeLine.size())
		{
			return m_TimeLine[index].Flag;
		}
		return false;
	}
	float GetProportion(int index)
	{
		if (m_TimeLine.empty() || index < 0 || index >= m_TimeLine.size())
		{
			return 1.0f;
		}
		else
		{
			if (index < m_CurrentIndex)
			{
				return 1.0f;
			}
			else
			{
				if (index < m_CurrentIndex + 1)
				{
					return m_Time / m_TimeLine[index].Time;
				}
				else
				{
					return 0.0f;
				}
			}	
		}
	}
	float GetTotalProportion(int beginIndex, int endIndex)
	{
		if (beginIndex >= endIndex || endIndex > m_TimeLine.size())
		{
			return 1.0f;
		}
		else
		{
			
			if (m_CurrentIndex <= beginIndex)
			{
				return 0.0f;
			}
			else
			{
				if (m_CurrentIndex > endIndex)
				{
					return 1.0f;
				}
			}
			float beginTime = 0.0f, endTime = 0.0f;
			int i;
			for (i = beginIndex + 1; i < m_CurrentIndex; i++)
			{
				beginTime += m_TimeLine[i].Time;
			}
			endTime = beginTime;
			beginTime += m_Time;
			for (i = m_CurrentIndex; i <= endIndex; i++)
			{
				endTime += m_TimeLine[i].Time;
			}
			return beginTime / endTime;
		}
		
		
	}
	const float GetTime()
	{
		return m_Time;
	}

private:
	float m_Time = 0.0f;
	int m_CurrentIndex = 0;
	bool m_StartupFlag = true;
	std::vector<TimePoint> m_TimeLine;
};