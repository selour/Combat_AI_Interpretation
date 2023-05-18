#include "stdafx.h"
#include "Animation2D.h"

namespace Engine
{
	Animation2D::Animation2D(unsigned int indexMax, bool loop)
		:m_Loop(loop), m_Play(true), m_Time(0), m_index(0), m_indexMax(indexMax)
	{
	
	}
	void Animation2D::OnUpdate(TimeStep ts)
	{
		if (m_Play)
		{
			m_Time += ts;
			while (m_Time > m_Playtime[m_index])
			{
				m_Time -= m_Playtime[m_index];
				m_index++;
				if (m_index == m_indexMax)
				{
					if (m_Loop)
					{
						m_index = 0;
					}
					else
					{
						m_Play = false;
						m_index--;
						break;
					}
				}
			}
		}
		
	}
	void Animation2D::AutoGenerateFrames(float offset, float playtime)
	{
		for (unsigned int i = 0; i < m_indexMax; i++)
		{
			m_TexCoordZs.push_back(offset + i);
			m_Playtime.push_back(playtime);
		}
	}

	void Animation2D::pushBackFrame(float texCoordZs, float playtime)
	{
		m_TexCoordZs.push_back(texCoordZs);
		m_Playtime.push_back(playtime);
	}
	void Animation2D::Play()
	{
		m_Play = true;
		m_Time = 0;
	}
	void Animation2D::Reset()
	{
		m_Time = 0;
		m_index = 0;
		m_Play = true;
	}
}