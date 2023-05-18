#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "Battle/Base/BlockDanger.h"
class TutorialDangerControl : public GameObject
{
public:
	TutorialDangerControl();
	//�����ʼ������
	virtual void Init() override;
	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) override;

	//������Ⱦ����
	//ʵ�������Ⱦ
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override;
	//����UI��Ⱦ
	virtual void OnImGuiRender() override;
private:
	GameTimer m_Timer;
	BlocKDangerSystem m_Danger;
};

