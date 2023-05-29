#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "Battle/Base/BlockDanger.h"
class TutorialDangerControl : public BlockDangerSystem
{
public:
	TutorialDangerControl();
	//对象初始化函数
	virtual void Init() override;
	//更新函数
	//基于时间的更新
	virtual void Update(float ts) override;

	//对象渲染函数
	//实际输出渲染
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//调试UI渲染
	virtual void OnImGuiRender() override;
	bool IsActive();
	void Active();
	void End();
private:
	int m_BPM = 100;
	int m_Count = 0;
	//-------------------
	//       [0]
	//    [2]   [3]
	//       [1]
	//---------------------
	int m_RandomMode = 0;
	GameTimer m_Timer;
};

