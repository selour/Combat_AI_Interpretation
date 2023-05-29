#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
class TutorialPost : public PostObject
{
public:
	TutorialPost();
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

