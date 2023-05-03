#include "GameLayer.h"
#include "imgui.h"
#include "TestScene.h"
#include "Battle/BattleScene.h"
void GameLayer::OnAttach()
{
	LayerPushScene(new TestScene());
	LayerPushScene(new TutorialBattleScene());
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Engine::TimeStep ts)
{
	m_FPS = int(1.0f / ts);

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

