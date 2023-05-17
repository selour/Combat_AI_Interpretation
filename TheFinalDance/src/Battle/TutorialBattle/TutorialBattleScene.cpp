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
	m_HeartFBO = std::make_shared<HeartFBO>();
	m_ParticleSystem = std::make_shared<ParticleCompomemt>();

	m_EnemyUI = std::make_shared<TutorialEnemyUI>();

	
	m_StagePost = std::make_shared<BrightFBO>();
	m_UIPost = std::make_shared<BrightFBO>();
	m_BloomPost = std::make_shared<Bloom>();
	m_Post = std::make_shared<TutorialPost>();

	m_BeatCounter = std::make_shared<BeatCounter>(100);
	m_Control = std::make_shared<TutorialBattleControl>();

	

	m_ObjectManager.SetCamera(0, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(0, m_HeartFBO);
	m_ObjectManager.Add(0, m_Heart);


	m_ObjectManager.SetCamera(1, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(1, m_StagePost);
	m_ObjectManager.Add(1, m_Stage);
	m_ObjectManager.Add(1, m_ParticleSystem);
	m_ObjectManager.Add(1, m_Enemy);
	m_ObjectManager.Add(1, m_Player);


	m_ObjectManager.SetCamera(2, m_CameraLibrary.Get("UI"));
	m_ObjectManager.SetPost(2, m_UIPost);
	m_ObjectManager.Add(2, m_EnemyUI);

	m_ObjectManager.SetPost(3, m_BloomPost);
	m_ObjectManager.Add(3, m_HeartFBO);
	m_ObjectManager.Add(3, m_StagePost);
	m_ObjectManager.Add(3, m_UIPost);
	

	m_ObjectManager.SetPost(4, m_Post);
	m_ObjectManager.Add(4, m_BloomPost);

	m_ObjectManager.Add(5, m_Post);
	
	m_ObjectManager.AddLogic(m_Control);
	m_ObjectManager.AddLogic(m_BeatCounter);
	
	
	m_BeatCounter->AddDelegate(std::bind(&Heart::OnBeat, m_Heart));
	m_BeatCounter->AddDelegate(std::bind(&TutorialEnemyUI::OnBeat, m_EnemyUI));

	m_Control->SetEnemyUI(m_EnemyUI);
	m_Control->SetEnemy(m_Enemy);
	m_Control->SetStage(m_Stage);
	m_Control->SetPlayer(m_Player);
	m_Control->SetHeart(m_Heart);
	m_Control->SetBeatCounter(m_BeatCounter);
	m_Control->SetPost(m_Post);
	m_Player->SetEnemy(m_Enemy);
	m_Player->SetStage(m_Stage);
	m_Player->SetParticleSystem(m_ParticleSystem);
	m_Enemy->SetStage(m_Stage);
	m_Enemy->SetParticleSystem(m_ParticleSystem);
	m_EnemyUI->SetEnemy(m_Enemy);
	m_HeartFBO->SetHeart(m_Heart);
	m_StagePost->SetDepthTest(false);

	
	//m_Control->StartShow();
	//m_Control->Start();

	m_Player->SetBlock(2 * 7 + 3);
	m_Enemy->SetBlock(3 * 7 + 3);
	
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
	m_ObjectManager.Update(ts);
}

void TutorialBattleScene::OnRender()
{
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	//Engine::RendererCommand::Clear();
	m_ObjectManager.Render();
}

void TutorialBattleScene::OnImGuiRender()
{
	ImGui::Begin("TutorialBattleScene");
	ImGui::Text("Time:%.2f s", m_Time);
	m_ObjectManager.OnImGuiRender();
	ImGui::End();
}
