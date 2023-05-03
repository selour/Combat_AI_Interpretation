#pragma once
#include "TimeStep.h"
#include "PlatformCommand.h"

namespace Engine
{
	class Timer
	{
	public:
		Timer()
		{
		}
		float GetProportion() const
		{
			if (m_StartupFlag || !m_TimeOutFlag)
			{
				return (PlatformCommand::GetTime() - m_TimeStart) / m_TimeSet;
			}
			else
			{
				return 1;
			}
			
		}
		void SetTime(float delayTime)
		{
			m_TimeStart = PlatformCommand::GetTime();
			m_TimeSet = delayTime;
			m_StartupFlag = true;
			m_TimeOutFlag = false;
		}

		void Clear()
		{
			m_StartupFlag = false;
			m_TimeOutFlag = false;
		}
		void Update()
		{
			
			if (m_StartupFlag)
			{
				if (m_TimeOutFlag)
				{
					Clear();
				}
				else
				{
					float time = PlatformCommand::GetTime();
					if (time >= m_TimeStart + m_TimeSet)
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
		float m_TimeStart = 0;
		float m_TimeSet = 0;
		bool m_StartupFlag = false;
		bool m_TimeOutFlag = false;
	
	};
};

