#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "BattleStage.h"
#include "ParticleComponent.h"
#include "BattleStage.h"
struct BeatTip
{
	void Clear()
	{
		IsActive = false;
		CheckFlag = false;
		BeatCheck.Clear();
	}
	void Update(float ts)
	{
		BeatCheck.Update(ts);
		if (IsActive)
		{
			if (CheckFlag == true)
			{
				if (BeatCheck.GetFlag(1))
				{
					CheckFlag = false;
					IsActive = false;
					BeatCheck.Clear();
				}
			}
			else
			{
				if (BeatCheck.GetFlag(0))
				{
					CheckFlag = true;
				}
				
			}
			
		}
	}
	bool IsActive = false;
	bool CheckFlag = false;
	GameTimeline BeatCheck;
};
class BattleEnemy : public GameObject
{
public:
	BattleEnemy()
	{
		m_BeatTips.resize(5);
	}
	void SetParticleSystem(std::shared_ptr<ParticleCompomemt> particleSystem)
	{
		m_ParticleSystem = particleSystem;
	}
	void SetStage(std::shared_ptr<BattleStage> stage)
	{
		m_Stage = stage;
	}
	void AddBeatTip(float tipTime)
	{
		if (m_Active)
		{
			m_BeatTips[m_CurrentBeatTip].IsActive = true;
			m_BeatTips[m_CurrentBeatTip].BeatCheck.Add(tipTime);
			m_BeatTips[m_CurrentBeatTip].BeatCheck.Add(m_CheckTime);
			m_BeatTips[m_CurrentBeatTip].BeatCheck.Start();
			m_CurrentBeatTip++;
			m_CurrentBeatTip %= m_BeatTips.size();

		}
	}
	void ClearBeatTip()
	{
		for (unsigned int i = 0; i < m_BeatTips.size(); i++)
		{
			m_BeatTips[i].Clear();
		}
	}
	void SetBlock(int index)
	{
		if (m_Stage->GetBlock(m_Current))
		{
			m_Stage->GetBlock(m_Current)->Occupy = false;
		}
		m_Current = index;
		m_Stage->GetBlock(m_Current)->Occupy = true;
	}
	StageBlock* GetBlock()
	{
		return m_Stage->GetBlock(m_Current);
	}
	bool OnHit(int step)
	{
		bool flag = false;
		for (unsigned int i = 0; i < m_BeatTips.size(); i++)
		{
			if (m_BeatTips[i].CheckFlag)
			{
				flag = true;
				HitBind(step);
				m_ParticleSystem->EmitParticle(5,m_Position,glm::vec3(1.0f));
				break;
			}
		}

		if (flag)
		{
			m_HitFlag.SetTime(0.5f);
		}
		return flag;
	}
	bool IsOnHit()
	{
		return m_HitFlag;
	}
protected:
	void OnUpdate(float ts)
	{
		if (m_Active)
		{
			m_HitFlag.Update(ts);
			
			for (unsigned int i = 0; i < m_BeatTips.size(); i++)
			{
				m_BeatTips[i].Update(ts);
			}
			m_Position = m_Stage->GetBlock(m_Current)->Postion.GetPostion();
		}
		
	}
	virtual void HitBind(int step) {};
	bool m_Active = true;
	glm::vec3 m_Position;
	float m_Size = 0.9f;
	float m_CheckTime = 0.1f;
	int m_Current = -1;
	GameTimer m_HitFlag;

	int m_CurrentBeatTip = 0;
	float m_BeatTipSize = 3.0f;
	glm::vec4 m_BeatTipColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 m_BeatCheckColor = glm::vec4(1.2f, 1.2f, 1.2f, 1.0f);
	std::vector<BeatTip> m_BeatTips;
	std::shared_ptr<BattleStage> m_Stage;
	std::shared_ptr<ParticleCompomemt> m_ParticleSystem;
	
};