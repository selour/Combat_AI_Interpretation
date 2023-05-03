#pragma once
#include "Core/Object.h"
#include "Core/GameTimer.h"
#include "Core/Transform.h"
#include "Engine.h"
class Heart : public GameObject
{
public:
	Heart();
	//对象初始化函数
	virtual void Init() override;
	//更新函数
	//基于时间的更新
	virtual void Update(float ts) override;
	//对象渲染函数
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//调试UI渲染
	virtual void OnImGuiRender() override;

	//事件函数
	void OnBeat();

	void Awake();

private:
	GameTimer m_Beat;
	Transform m_Main;
	Transform m_Part[5];

	bool m_Awake = false;

};

