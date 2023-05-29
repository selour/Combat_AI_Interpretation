#include "TutorialBattleScene.h"

void TutorialBattleScene::OnAttach()
{
	auto MainCamera = m_CameraLibrary.AddOrthographicCamera("Main");
	auto UICamera = m_CameraLibrary.AddOrthographicCamera("UI");
	MainCamera->SetFieldOfView(6.0f);
	UICamera->SetFieldOfView(1.0f);
	m_ResourceManager.Init();



	m_ObjectManager.SetResourceManager(&m_ResourceManager);
	m_ObjectManager.SetCameraLibrary(&m_CameraLibrary);
	m_ObjectManager.Reset(6);


	m_Heart = std::make_shared<Heart>();

	m_Stage = std::make_shared<TutorialBattleStage>();
	m_Player = std::make_shared<TutorialBattlePlayer>();
	m_Enemy = std::make_shared<TutorialBattleEnemy>();
	m_Danger = std::make_shared<TutorialDangerControl>();

	m_HeartFBO = std::make_shared<HeartFBO>();
	m_ParticleSystem = std::make_shared<ParticleCompomemt>();

	m_EnemyUI = std::make_shared<TutorialEnemyUI>();
	m_PlayerUI = std::make_shared<TutorialPlayerUI>();
	
	m_StagePost = std::make_shared<BrightFBO>();
	m_UIPost = std::make_shared<BrightFBO>();
	m_BloomPost = std::make_shared<Bloom>();
	m_Post = std::make_shared<TutorialPost>();

	m_BeatCounter = std::make_shared<BeatCounter>(100);
	//m_Control = std::make_shared<TutorialBattleControl>();

	

	m_ObjectManager.SetCamera(0, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(0, m_HeartFBO);
	m_ObjectManager.Add(0, m_Heart);


	m_ObjectManager.SetCamera(1, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(1, m_StagePost);
	m_ObjectManager.Add(1, m_Stage);
	m_ObjectManager.Add(1, m_ParticleSystem);
	m_ObjectManager.Add(1, m_Enemy);
	m_ObjectManager.Add(1, m_Player);
	m_ObjectManager.Add(1, m_Danger);

	m_ObjectManager.SetCamera(2, m_CameraLibrary.Get("UI"));
	m_ObjectManager.SetPost(2, m_UIPost);
	m_ObjectManager.Add(2, m_PlayerUI);
	m_ObjectManager.Add(2, m_EnemyUI);


	m_ObjectManager.SetPost(3, m_BloomPost);
	m_ObjectManager.Add(3, m_HeartFBO);
	m_ObjectManager.Add(3, m_StagePost);
	m_ObjectManager.Add(3, m_UIPost);
	

	m_ObjectManager.SetPost(4, m_Post);
	m_ObjectManager.Add(4, m_BloomPost);

	m_ObjectManager.Add(5, m_Post);
	
	
	m_ObjectManager.AddLogic(m_BeatCounter);
	
	
	m_BeatCounter->AddDelegate(std::bind(&Heart::OnBeat, m_Heart));
	m_BeatCounter->AddDelegate(std::bind(&TutorialEnemyUI::OnBeat, m_EnemyUI));

	

	m_Player->SetEnemy(m_Enemy);
	m_Player->SetStage(m_Stage);
	m_Player->SetParticleSystem(m_ParticleSystem);
	m_Enemy->SetStage(m_Stage);
	m_Enemy->SetParticleSystem(m_ParticleSystem);
	m_Danger->SetStage(m_Stage);
	m_EnemyUI->SetEnemy(m_Enemy);
	m_PlayerUI->SetPlayer(m_Player);
	m_HeartFBO->SetHeart(m_Heart);
	m_StagePost->SetDepthTest(false);

	


	m_Player->SetBlock(2 * 7 + 3);
	m_Enemy->SetBlock(3 * 7 + 3);

	m_State = 0;
	m_Awake.SetTime(2.0f);

	StartShow();
	
}

void TutorialBattleScene::Reset()
{
}

void TutorialBattleScene::OnDetach()
{
	
}

void TutorialBattleScene::OnUpdate(Engine::TimeStep ts)
{
	m_Time += ts;
	UpdateState(ts);
	m_ObjectManager.Update(ts);
}

void TutorialBattleScene::OnRender()
{
	m_ObjectManager.Render();
}

void TutorialBattleScene::OnImGuiRender()
{
	ImGui::Begin("TutorialBattleScene");
	ImGui::Text("Time:%.2f s", m_Time);
	m_ObjectManager.OnImGuiRender();
	ImGui::End();
}



void TutorialBattleScene::UpdateState(float ts)
{
	switch (m_State)
	{
	case 0:
		//场景启动阶段
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_Awake.SetTime(60.0f / (float)m_Bpm * 8.0f);
			m_Awake.SetLoop(true);
			m_State = 1;
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_startup"));
		}
		break;
	case 1:
		//开场终末拍教学
		//击中后开始开场动画
		m_Awake.Update(ts);
		if (m_Enemy->IsOnHit())
		{
			StartShow();
		}
		if (m_Awake.IsTimeOut())
		{
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_startup"));
		}
		break;
	case 2:
		//开场动画等待
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("switch"));
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
		//Payer启动等待
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 4;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 16.0f);
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_metronome_start"));
		}
		break;
	case 4:
		//移动教学阶段(移动加终末拍教学跳回)
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 5;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 2.0f);
			m_Player->SetEnable(false);
			m_Player->ClearStep();
			m_Player->ChangeColor();
			m_EnemyUI->Awake();
			m_Post->GetNoise()->SetTime(60.0f / (float)m_Bpm * 2.0f + 0.02f);
			m_Post->Awake();
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("white_noise"));
		}
		break;
	case 5:
		//白噪音花屏等待阶段（循环开始）
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			//如果敌人血量少于50进入危险阶段
			if (m_Enemy->GetLife() <= 50)
			{
				m_State = 7;
				SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("switch"));
				m_Awake.SetTime(60.0f / 100.0f);
				m_Enemy->SetBlock(3 * 7 + 3);
				m_Player->SetBlock(2 * 7 + 3);
				m_Player->SetEnable(true);
				m_Player->OnWait();
				m_EnemyUI->OnWait();
				m_BeatCounter->SetBPM(100);
			}
			else
			{
				SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("switch"));
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

		}
		break;
	case 6:
		//Payer启动等待
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			m_State = 4;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 8.0f);
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			m_Post->GetRhythm()->SetTime(60.0f / (float)m_Bpm * 8.0f);
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_metronome_loop"));
		}
		break;
	case 7:
		//Player启动等待
		m_Awake.Update(ts);
		if (m_Awake.GetProportion() > 0.5f)
		{
			if (!m_Danger->IsActive())
			{
				m_Danger->Active();
			}
		}
		if (m_Awake.IsTimeOut())
		{
			m_State = 8;
			m_Awake.SetTime(60.0f / (float)m_Bpm * 8.0f);
			m_Awake.SetLoop(true);
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			m_Post->GetRhythm()->SetTime(60.0f / (float)m_Bpm * 8.0f);
			SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_metronome_loop2"), true);
		}
		break;
	case 8:
		//危险阶段循环
		m_Awake.Update(ts);
		CheckWinOrLost();
		if (m_Awake.GetProportion() > 15.0f / 16.0f)
		{
			if (!m_Danger->IsActive())
			{
				m_Danger->Active();
			}
		}
		if (m_Awake.IsTimeOut())
		{
			m_Enemy->AddBeatTip(60.0f / (float)m_Bpm * 7.0f);
			m_Post->GetRhythm()->SetTime(60.0f / (float)m_Bpm * 8.0f);
		}
		break;
	case 999:
		m_Awake.Update(ts);
		if (m_Awake.IsTimeOut())
		{
			SoundEngine::StopAllSound();
			GlobalFlag::SetShouldExitBattle(true);
		}
		break;

	}

}

void TutorialBattleScene::CheckWinOrLost()
{
	if (m_Enemy->GetLife() == 0)
	{
		GlobalFlag::SetBattleWin(true);
		EndShow();
	}
	if (m_Player->GetLife() == 0)
	{
		GlobalFlag::SetBattleWin(false);
		EndShow();
	}
	
}
void TutorialBattleScene::StartShow()
{
	SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("wind"));
	m_State = 2;
	m_Player->SetEnable(false);
	m_Stage->StartShow();
	m_EnemyUI->StartShow();
	m_Awake.SetTime(4.0f);
	m_Awake.SetLoop(false);
}

void TutorialBattleScene::EndShow()
{
	SoundEngine::StopAllSound(m_ObjectManager.GetSoundSourceLibrary()->Get("tutorial_metronome_loop2"));
	SoundEngine::Play2D(m_ObjectManager.GetSoundSourceLibrary()->Get("white_noise"), true);
	m_Awake.SetTime(5.0f);
	m_State = 999;
	m_Post->End();
	m_Player->SetEnable(false);
	m_Danger->End();
	m_Stage->Clear();
}