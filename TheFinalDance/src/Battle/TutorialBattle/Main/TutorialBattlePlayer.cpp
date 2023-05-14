#include "TutorialBattlePlayer.h"

void TutorialBattlePlayer::Init()
{
}

void TutorialBattlePlayer::Update(float ts)
{
	OnUpdate(ts);
	PlayerControl();
}

void TutorialBattlePlayer::Render(std::shared_ptr<Engine::Camera> camera)
{
	OnRender(camera);
}

void TutorialBattlePlayer::OnImGuiRender()
{
}
