#pragma once
#include "ObjectManager.h"
#include "Engine.h"

class BrightFBO : public PostObject
{
public:
	BrightFBO();
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

	void SetDepthTest(bool enable);
private:
	bool m_DepthTest = true;
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
};

