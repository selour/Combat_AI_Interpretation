#pragma once
#include "Battle/Base/BattleEnemy.h"
#include "Core/GameTimer.h"
class TutorialBattleEnemy : public BattleEnemy
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

	virtual void HitBind(int step) override;


	void Unlock();
	void RandomBlock();

	int GetLife();

private:
	bool m_LifeLock = true;
	int m_Life = 100;
};

