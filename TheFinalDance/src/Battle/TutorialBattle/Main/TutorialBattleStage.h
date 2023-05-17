#pragma once
#include "Battle/Base/BattleStage.h"
#include "Core/GameTimer.h"
class TutorialBattleStage : public BattleStage
{
public:
	TutorialBattleStage();
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

	void StartShow();
	void Start();
private:
	void BlockBack();
	GameTimer m_Start;
	int m_Number;
	float m_Brightness = 1.0f;
	glm::vec3 m_Color = { 1.0f,1.0f,1.0f };
};

