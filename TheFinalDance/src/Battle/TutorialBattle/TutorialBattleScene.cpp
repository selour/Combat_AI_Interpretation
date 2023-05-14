#include "TutorialBattleScene.h"

void TutorialBattleScene::OnAttach()
{
	auto MainCamera = m_CameraLibrary.AddOrthographicCamera("Main");
	auto UICamera = m_CameraLibrary.AddOrthographicCamera("UI");

	m_ResourceManager.Init();



	m_ObjectManager.SetResourceManager(&m_ResourceManager);
	m_ObjectManager.SetCameraLibrary(&m_CameraLibrary);
	m_ObjectManager.Reset(5);


	auto heart = std::make_shared<Heart>();

	auto stage = std::make_shared<TutorialBattleStage>();
	auto player = std::make_shared<TutorialBattlePlayer>();
	
	auto backgroundFBO = std::make_shared<BackgroundFBO>();
	

	auto stagePost = std::make_shared<MainFBO>();
	auto bloomPost = std::make_shared<Bloom>();
	
	m_ObjectManager.SetCamera(0, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(0, backgroundFBO);
	m_ObjectManager.Add(0, heart);

	m_ObjectManager.SetCamera(1, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(1, stagePost);
	m_ObjectManager.Add(1, stage);
	m_ObjectManager.Add(1, player);
	
	m_ObjectManager.SetCamera(2, m_CameraLibrary.Get("Main"));
	m_ObjectManager.SetPost(2, bloomPost);
	m_ObjectManager.Add(2, backgroundFBO);
	m_ObjectManager.Add(2, stagePost);


	//m_ObjectManager.SetCamera(3, m_CameraLibrary.Get("Main"));
	m_ObjectManager.Add(3, bloomPost);
	

	

	auto beatCounter = std::make_shared<BeatCounter>(100);
	beatCounter->AddDelegate(std::bind(&Heart::OnBeat, heart));
	m_ObjectManager.AddLogic(beatCounter);
	
	heart->Awake();
	player->SetInitBlock(stage->GetBlock(3 * 7 + 3));
	player->SetStage(stage);

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
