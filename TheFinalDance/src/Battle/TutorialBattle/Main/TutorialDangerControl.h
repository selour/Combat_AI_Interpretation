#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "Battle/Base/BlockDanger.h"
class TutorialDangerControl : public BlockDangerSystem
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
	bool IsActive();
	void Active();
	void End();
private:
	int m_BPM = 100;
	int m_Count = 0;
	//-------------------
	//       [0]
	//    [2]   [3]
	//       [1]
	//---------------------
	int m_RandomMode = 0;
	GameTimer m_Timer;
};

