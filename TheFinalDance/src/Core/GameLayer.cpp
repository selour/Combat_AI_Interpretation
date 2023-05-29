#include "GameLayer.h"
#include "imgui.h"
#include "TestScene.h"

void GameLayer::OnAttach()
{
	m_MapScene = new MapScene();
	LayerPushScene(m_MapScene);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Engine::TimeStep ts)
{
	m_FPS = int(1.0f / ts);


	if (GlobalFlag::ShouldInBattle())
	{
		m_BattleScene = new TutorialBattleScene();
		LayerPushScene(m_BattleScene);
		GlobalFlag::SetShouldInBattle(false);
		GlobalFlag::SetInBattle(true);
		m_MapScene->InBattle();
	}
	if (GlobalFlag::ShouldExitBattle())
	{
		LayerPopScene(m_BattleScene);
		delete m_BattleScene;
		GlobalFlag::SetInBattle(false);
		GlobalFlag::SetShouldExitBattle(false);
		m_MapScene->OutBattle();
		
	}
		


	for (Scene* scene : m_SceneStack)
	{
		scene->OnUpdate(ts);
	}

	for (Scene* scene : m_SceneStack)
	{
		scene->OnRender();
	}
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("GameLayer");
	ImGui::Text("%dFPS", m_FPS);
	ImGui::Text("InBattle:%d", GlobalFlag::InBattle());
	ImGui::End();
	for (Scene* scene : m_SceneStack)
	{
		scene->OnImGuiRender();
	}

}

void GameLayer::OnEvent(Engine::Event& event)
{
}

void GameLayer::LayerPushScene(Scene* scene)
{
	m_SceneStack.PushScene(scene);
	scene->OnAttach();
}

void GameLayer::LayerPopScene(Scene* scene)
{
	m_SceneStack.PopScene(scene);
	scene->OnDetach();
}

void GameLayer::LayerPushOverScene(Scene* scene)
{
	m_SceneStack.PushOverScene(scene);
	scene->OnAttach();
}

void GameLayer::LayerPopOverScene(Scene* scene)
{
	m_SceneStack.PopOverScene(scene);
	scene->OnDetach();
}

