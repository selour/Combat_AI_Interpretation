#pragma once
#include "Battle/Base/BattleEnemy.h"
#include "Core/GameTimer.h"
class TutorialBattleEnemy : public BattleEnemy
{
public:
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

	virtual void HitBind(int step) override;


	void Unlock();
	void RandomBlock();

	int GetLife();

private:
	bool m_LifeLock = true;
	int m_Life = 100;
};

