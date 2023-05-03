#pragma once
class GameTimer
{
public:
	GameTimer()
	{
	}
	float GetProportion() const
	{
		if (m_StartupFlag || !m_TimeOutFlag)
		{
			return m_Time / m_TimeSet;
		}
		else
		{
			return 1;
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