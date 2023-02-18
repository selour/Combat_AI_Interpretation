#include "BattleLayer.h"

//-----------------------------------ΩÃ≥Ã’Ω∂∑----------------------------------------
void TutorialBattle::OnAttach()
{
	SoundEngine = irrklang::createIrrKlangDevice();
	m_Bpm = 100;
	m_time = 0;
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{

}
