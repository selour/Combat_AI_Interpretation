#include "TutorialBattlePlayer.h"
#include <imgui.h>
void TutorialBattlePlayer::Init()
{
}

void TutorialBattlePlayer::Update(float ts)
{
	OnUpdate(ts);
}

void TutorialBattlePlayer::Render(std::shared_ptr<Engine::Camera> camera)
{
	OnRender(camera);
}

void TutorialBattlePlayer::OnImGuiRender()
{
	ImGui::Text("Player:");
	ImGui::DragFloat("PlayerBrightness", &m_Brightness, 0.001f, 0.0f, 5.0f);
}

void TutorialBattlePlayer::ChangeColor()
{
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Color = glm::vec4(color * m_Brightness, 1.0f);
}
