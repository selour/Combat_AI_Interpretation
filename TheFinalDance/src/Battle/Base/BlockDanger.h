#pragma once
#include "BattleStage.h"

struct BlockDanger
{
	bool Awake = false;
	int BlockIndex = -1;
	float Time = 0;
};

class BlocKDangerSystem
{
public:
	BlocKDangerSystem(unsigned int size = 50)
	{
		m_Dangers.resize(size);
	}
	void Update(float ts)
	{
		for (int i = 0; i < m_Dangers.size(); i++)
		{
			if (m_Dangers[i].Awake)
			{
				m_Dangers[i].Time -= ts;
				if (m_Dangers[i].Time <= 0.0f)
				{
					m_Stage->GetBlock(m_Dangers[i].BlockIndex)->Danger = false;
					m_Dangers[i].Awake = false;
				}
			}
			
		}
	}

	void Submit(int index, float time)
	{
		m_Dangers[index].Awake = true;
		m_Dangers[index].BlockIndex = index;
		m_Dangers[index].Time = time;
		m_Stage->GetBlock(index)->Danger = true;
		m_Index++;
		m_Index %= m_Dangers.size();
	}

private:
	int m_Index = 0;
	std::vector<BlockDanger> m_Dangers;
	std::shared_ptr<BattleStage> m_Stage;
};
