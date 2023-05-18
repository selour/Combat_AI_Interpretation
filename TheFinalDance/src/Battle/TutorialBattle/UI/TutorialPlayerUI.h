#pragma once
#include "Battle/Base/PlayerUI.h"
class TutorialPlayerUI : public PlayerUI
{
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
};

