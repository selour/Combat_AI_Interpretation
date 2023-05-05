#pragma once
#include "Battle/Base/BattleStage.h"
class TutorialBattleStage : public BattleStage
{
public:
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
};

