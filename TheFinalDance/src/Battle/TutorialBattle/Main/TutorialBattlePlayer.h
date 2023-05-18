#pragma once
#include "Battle/Base/BattlePlayer.h"
class TutorialBattlePlayer : public BattlePlayer
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
	void ChangeColor();
private:
	float m_Brightness = 2.0f;
};

