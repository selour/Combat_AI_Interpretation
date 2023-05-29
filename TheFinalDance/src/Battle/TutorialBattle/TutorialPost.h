#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
class TutorialPost : public PostObject
{
public:
	TutorialPost();
	//对象初始化函数
	virtual void Init() override;
	//更新函数
	//基于时间的更新
	virtual void Update(float ts) override;

	//对象渲染函数
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//调试UI渲染
	virtual void OnImGuiRender() override;

	virtual void Bind() override;
	virtual void UnBind() override;

	GameTimer* GetRhythm()
	{
		return &m_Rhythm;
	}

	GameTimer* GetNoise()
	{
		return &m_Noise;
	}
	void Awake()
	{
		m_Awake = true;
	}
	void End()
	{
		m_Noise.SetTime(5.02f);
	}
private:
	float m_Time = 0;
	bool m_Awake = false;
	GameTimer m_Noise;
	GameTimer m_Rhythm;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
	
};

