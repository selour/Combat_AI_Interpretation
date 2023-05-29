#include "stdafx.h"
#include "Animation2D.h"

namespace Engine
{
	Animation2D::Animation2D(unsigned int indexMax, bool loop)
		:m_Loop(loop), m_Play(true), m_Time(0), m_Index(0), m_IndexMax(indexMax)
	{
	
	}
	void Animation2D::OnUpdate(TimeStep ts)
	{
		if (m_Play)
		{
			m_Time += ts;
			while (m_Time > m_Aniamtion[m_Index].Playtime)
			{
				m_Time -= m_Aniamtion[m_Index].Playtime;
				m_Index++;
				if (m_Index == m_IndexMax)
				{
					if (m_Loop)
					{
						m_Index = 0;
					}
					else
					{
						m_Play = false;
						m_Index--;
						break;
					}
				}
			}
		}
		
	}
	void Animation2D::AutoGenerateFrames(float offset, float playtime)
	{
		for (unsigned int i = 0; i < m_IndexMax; i++)
		{
			m_Aniamtion.push_back(Animation2DFrame(offset + i, playtime));
		}
	}

	void Animation2D::PushBackFrame(float texCoordZs, float playtime)
	{
		m_Aniamtion.push_back(Animation2DFrame(texCoordZs, playtime));
	}
	void Animation2D::Play()
	{
		m_Play = true;
		m_Time = 0;
	}
	void Animation2D::Reset()
	{
		m_Time = 0;
		m_Index = 0;
		m_Play = true;
	}
}