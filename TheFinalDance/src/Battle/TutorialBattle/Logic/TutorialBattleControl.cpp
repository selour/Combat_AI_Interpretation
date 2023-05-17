#include "TutorialBattleControl.h"
#include <imgui.h>
void TutorialBattleControl::Init()
{
	m_State = 0;
	m_Awake.SetTime(2.0f);
}

void TutorialBattleControl::Update(float ts)
{
	switch (m_State)
	{
	case 0:
		//������ĩ�Ľ�ѧ
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_Beat.SetTime(60.0f / (float)m_Bpm * 8.0f);
			m_Beat.SetLoop(true);
			m_State = 1;
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("tutorial_startup"));
		}
		break;
	case 1:
		//���к�ʼ��������
		if (m_Enemy->IsOnHit())
		{
			StartShow();
		}
		m_Beat.Update(ts);
		if (m_Beat.IsTimeOut())
		{
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("tutorial_startup"));
		}
		break;
	case 2:
		//���������ȴ�
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("switch"));
			m_Awake.SetTime(60.0f / 100.0f);
			m_State = 3;
			m_Player->SetEnable(true);
			m_Stage->Start();
			m_Player->OnWait();
			m_Enemy->Unlock();
			m_EnemyUI->OnWait();
			m_BeatCounter->SetBPM(100);
		}
		break;
	case 3:
		//Payer�����ȴ�
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 4;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 16.0f);
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("tutorial_metronome_start"));
		}
		break;
	case 4:
		//�ƶ���ѧ�׶�(�ƶ�����ĩ�Ľ�ѧ����)
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 5;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 2.0f);
			m_Player->SetEnable(false);
			m_Player->ClearStep();
			m_Player->ChangeColor();
			m_EnemyUI->Awake();
			m_Post->GetNoise()->SetTime(60.0f / (float)m_Bpm * 2.0f);
			m_Post->Awake();
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("white_noise"));
		}
		break;
	case 5:
		//�����������ȴ��׶Σ�ѭ����ʼ��
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("switch"));
			m_Awake.SetTime(60.0f / 100.0f);
			m_State = 6;
			m_Heart->Awake();
			m_Enemy->RandomBlock();
			m_Player->SetBlock(3 * 7 + 3);
			m_Player->SetEnable(true);
			m_Player->OnWait();
			m_EnemyUI->OnWait();
			m_BeatCounter->SetBPM(100);
		}
		break;
	case 6:
		//Payer�����ȴ�
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 4;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 8.0f);
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			m_Post->GetRhythm()->SetTime(60.0f / (float)m_Bpm * 8.0f);
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("tutorial_metronome_loop"));
		}
		break;

	}
	
	
}

void TutorialBattleControl::OnImGuiRender()
{
	ImGui::Text("BattleControl:");
	ImGui::Text("IsTimeOut:%d", m_Beat.IsTimeOut());
}

void TutorialBattleControl::StartShow()
{
	SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("wind"));
	m_State = 2;
	m_Player->SetEnable(false);
	m_Stage->StartShow();
	m_EnemyUI->StartShow();
	m_Awake.SetTime(4.0f);
}





void TutorialBattleControl::SetEnemyUI(std::shared_ptr<TutorialEnemyUI> enemyUI)
{
	m_EnemyUI = enemyUI;
}

void TutorialBattleControl::SetEnemy(std::shared_ptr<TutorialBattleEnemy> enemy)
{
	m_Enemy = enemy;
	
}

void TutorialBattleControl::SetStage(std::shared_ptr<TutorialBattleStage> stage)
{
	m_Stage = stage;
}

void TutorialBattleControl::SetPlayer(std::shared_ptr<TutorialBattlePlayer> player)
{
	m_Player = player;
}

void TutorialBattleControl::SetHeart(std::shared_ptr<Heart> heart)
{
	m_Heart = heart;
}

void TutorialBattleControl::SetBeatCounter(std::shared_ptr<BeatCounter> beatCounter)
{
	m_BeatCounter = beatCounter;
}

void TutorialBattleControl::SetPost(std::shared_ptr<TutorialPost> post)
{
	m_Post = post;
}
