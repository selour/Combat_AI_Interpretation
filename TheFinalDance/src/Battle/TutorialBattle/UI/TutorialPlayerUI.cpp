#include "TutorialPlayerUI.h"

void TutorialPlayerUI::Init()
{
}

void TutorialPlayerUI::Update(float ts)
{
	OnUpdate(ts);
}

void TutorialPlayerUI::Render(std::shared_ptr<Engine::Camera> camera)
{
	OnRender(camera);
}

void TutorialPlayerUI::OnImGuiRender()
{
}
