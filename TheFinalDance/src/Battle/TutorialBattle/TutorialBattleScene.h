#pragma once
#include "Core/Scene.h"
#include "Core/ObjectManager.h"
#include "Core/Bloom.h"
#include "Core/GenericFBO.h"
#include "Core/BrightFBO.h"

#include "Battle/Base/BeatCounter.h"
#include "Battle/Base/ParticleComponent.h"
#include "Background/Heart.h"
#include "Background/HeartFBO.h"
#include "Main/TutorialBattleStage.h"
#include "Main/TutorialBattleEnemy.h"
#include "Main/TutorialBattlePlayer.h"
#include "UI/TutorialEnemyUI.h"
#include "UI/TutorialPlayerUI.h"
#include "Logic/TutorialBattleControl.h"

#include "TutorialPost.h"
#include "TutorialResourceManager.h"

class TutorialBattleScene : public Scene
{
public:
	TutorialBattleScene()
		:Scene("TutorialBattle")
	{

	}

	virtual void OnAttach() override;

	virtual void Reset() override;

	virtual void OnDetach() override;

	virtual void OnUpdate(Engine::TimeStep ts) override;

	virtual void OnRender() override;

	virtual void OnImGuiRender() override;
	


private:
	float m_Time = 0;
	TutorialResourceManager m_ResourceManager;

	ObjectManager m_ObjectManager;
	
	Engine::CameraLibrary m_CameraLibrary;


	std::shared_ptr<Heart> m_Heart;

	std::shared_ptr<TutorialBattleStage> m_Stage;
	std::shared_ptr<TutorialBattlePlayer> m_Player;
	std::shared_ptr<TutorialBattleEnemy> m_Enemy;
	
	std::shared_ptr<ParticleCompomemt> m_ParticleSystem;

	std::shared_ptr<HeartFBO> m_HeartFBO;
	std::shared_ptr<BrightFBO> m_StagePost;
	std::shared_ptr<BrightFBO> m_UIPost;

	std::shared_ptr<Bloom> m_BloomPost;
	std::shared_ptr<TutorialPost> m_Post;



	std::shared_ptr<BeatCounter> m_BeatCounter;
	std::shared_ptr<TutorialBattleControl> m_Control;
	std::shared_ptr<TutorialEnemyUI> m_EnemyUI;
	std::shared_ptr<TutorialPlayerUI> m_PlayerUI;


};
