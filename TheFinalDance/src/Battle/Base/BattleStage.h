#pragma once
#include "Core/Object.h"
#include "Core/Transform.h"
#include "Engine.h"
struct StageBlock
{
public:

	Transform m_Transform = Transform(true, true, true);

	int Step = 0;
	bool Awake = false;
	bool Occupy = false;
	bool Danger = false;
	
	
	StageBlock* Link[4] = { nullptr, nullptr, nullptr, nullptr };
};
class BattleStage : public GameObject
{
protected:
	std::vector<StageBlock> m_Stage;
};