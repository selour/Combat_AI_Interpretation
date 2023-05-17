#pragma once
#include "Core/ObjectManager.h"
#include "Heart.h"
#include "Engine.h"
class HeartFBO : public PostObject
{
public:
	HeartFBO();
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

	void SetHeart(std::shared_ptr<Heart> heart)
	{
		m_Heart = heart;
	}
private:
	std::shared_ptr<Heart> m_Heart;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
	float m_Brightness = 1.0f;
};

