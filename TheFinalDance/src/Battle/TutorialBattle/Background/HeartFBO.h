#pragma once
#include "Core/ObjectManager.h"
#include "Heart.h"
#include "Engine.h"
class HeartFBO : public PostObject
{
public:
	HeartFBO();
	//�����ʼ������
	virtual void Init() override;
	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) override;

	//������Ⱦ����
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//����UI��Ⱦ
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

