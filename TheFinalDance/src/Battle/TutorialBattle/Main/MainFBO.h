#pragma once
#include "Core/ObjectManager.h"
#include "Engine.h"

class MainFBO : public PostObject
{
public:
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
private:
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
};

