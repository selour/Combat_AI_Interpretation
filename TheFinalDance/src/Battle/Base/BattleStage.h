#pragma once
#include "Core/Object.h"
#include "Core/Transform.h"
#include "BattleStage.h"
#include "Engine.h"

enum MoveForward
{
	Up = 0, Down = 1, Left = 2, Right = 3
};

struct StageBlock
{
public:
	void Init()
	{
		Number1.SetFather(&Postion);
		Number2.SetFather(&Postion);
		Number1.SetPostion(glm::vec3(-0.3f, 0.3f, 0.0f));
		Number1.SetScale(glm::vec3(0.25f));
		Number2.SetPostion(glm::vec3(-0.05f, 0.3f, 0.0f));
		Number2.SetScale(glm::vec3(0.25f));
	}
	bool CanMove(MoveForward forward)
	{
		return Link[forward] != nullptr && Link[forward]->Awake && !Link[forward]->Occupy;
	}
	Transform Postion;
	Transform Number1,Number2;
	int Step = 0;
	bool Awake = false;
	bool Occupy = false;
	bool Danger = false;
	
	//-------Link----------
	//       [0]
	//    [2]   [3]
	//       [1]
	//---------------------
	StageBlock* Link[4] = { nullptr, nullptr, nullptr, nullptr };
};
class BattleStage : public GameObject
{
public:
	//Çå¿Õ²½Êý
	void ClearStep()
	{
		for (unsigned int i = 0; i < m_Stage.size(); i++)
		{
			m_Stage[i].Step = 0;
		}
	}
	StageBlock* GetBlock(int index)
	{
		if (index < m_Stage.size())
		{
			return &m_Stage[index];
		}
		else
		{
			return nullptr;
		}
		
	}
protected:
	std::vector<StageBlock> m_Stage;
	Transform m_MainTransform;

	
	
};