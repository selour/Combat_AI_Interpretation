#pragma once
#include "Battle/Base/BattleUI.h"
#include "Battle/TutorialBattle/Main/TutorialBattleEnemy.h"
class TutorialEnemyUI : public BattleUI
{
public:
	TutorialEnemyUI();
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

	void Awake();

	void SetEnemy(std::shared_ptr<TutorialBattleEnemy> enemy);

	void OnBeat();
	void OnWait();
	void StartShow();
private:
	
	Transform m_Panel;
	Transform m_PanelBloom;

	Transform m_Pointer;
	Transform m_RotationPoint;
	Transform m_PointerPole;
	Transform m_PointerBloom;

	Transform m_Knob;
	Transform m_Base;

	Transform m_LifeSlot;
	Transform m_Slot[20];
	int m_SlotNumber = 0;
	float m_topAlpha = 0;
	
	bool m_Awake = false;
	bool m_Wait = false;
	int m_Forward = -1;
	GameTimer m_Metronome;

	float m_KnobRotation = 0;
	int m_RotationCount = 0;
	GameTimer m_Rotation;

	std::shared_ptr<TutorialBattleEnemy> m_Enemy;
};

