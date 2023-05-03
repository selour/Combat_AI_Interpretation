#include "TutorialBattleScene.h"

void TutorialBattleScene::OnAttach()
{
	auto backgroundCamera = m_CameraLibrary.AddOrthographicCamera("Background");
	auto UICamera = m_CameraLibrary.AddOrthographicCamera("UI");

	m_ResourceManager.Init();
	m_ObjectManager.SetResourceManager(&m_ResourceManager);
	m_ObjectManager.SetCameraLibrary(&m_CameraLibrary);
	m_ObjectManager.Reset(5);
	m_ObjectManager.SetCamera(0, m_CameraLibrary.Get("Background"));


	m_Heart = std::make_shared<Heart>();

	m_Heart->Awake();

	m_ObjectManager.Add(0, m_Heart);


	m_BeatCounter = std::make_shared<BeatCounter>(100);
	m_BeatCounter->AddDelegate(std::bind(&Heart::OnBeat, m_Heart));
	m_ObjectManager.AddLogic(m_BeatCounter);

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
	m_ObjectManager.Render();
}

void TutorialBattleScene::OnImGuiRender()
{
	ImGui::Begin("TutorialBattleScene");
	ImGui::Text("Time:%.2f s", m_Time);
	ImGui::End();
	m_ObjectManager.OnImGuiRender();
}
