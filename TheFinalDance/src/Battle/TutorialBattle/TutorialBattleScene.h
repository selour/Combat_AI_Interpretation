#pragma once
#include "Core/Scene.h"
#include "Core/ObjectManager.h"
#include "Core/Bloom.h"
#include "Core/GenericFBO.h"
#include "Battle/Base/BeatCounter.h"
#include "Background/Heart.h"
#include "Background/BackgroundFBO.h"
#include "Main/TutorialBattleStage.h"

#include "TutorialResourceManager.h"

class TutorialBattleScene : public Scene
{
public:
	TutorialBattleScene()
		:Scene("TutorialBattle"), m_ParticleSystem(500)
	{

	}

	virtual void OnAttach() override;


	virtual void OnDetach() override;

	virtual void OnUpdate(Engine::TimeStep ts) override;

	virtual void OnRender() override;

	virtual void OnImGuiRender() override;
	


private:
	float m_Time = 0;
	TutorialResourceManager m_ResourceManager;
	Engine::ParticleSystem m_ParticleSystem;

	ObjectManager m_ObjectManager;
	
	Engine::CameraLibrary m_CameraLibrary;

};
