#include "BattleLayer.h"

//-----------------------------------�̳�ս��----------------------------------------
void TutorialBattle::OnAttach()
{
	SoundEngine = irrklang::createIrrKlangDevice();
	m_Bpm = 100;
	m_time = 0;
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{

}
