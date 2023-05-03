#pragma once
#include "Core/Object.h"
#include "Core/GameTimer.h"
#include "Core/Transform.h"
#include "Engine.h"
class Heart : public GameObject
{
public:
	Heart();
	//�����ʼ������
	virtual void Init() override;
	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) override;
	//������Ⱦ����
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//����UI��Ⱦ
	virtual void OnImGuiRender() override;

	//�¼�����
	void OnBeat();

	void Awake();

private:
	GameTimer m_Beat;
	Transform m_Main;
	Transform m_Part[5];

	bool m_Awake = false;

};

