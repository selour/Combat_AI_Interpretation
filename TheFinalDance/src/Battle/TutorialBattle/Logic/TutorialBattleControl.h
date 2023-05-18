#pragma once
#include "Core/Object.h"
#include "Core/GameTimer.h"
#include "Battle/TutorialBattle/Main/TutorialBattleStage.h"
#include "Battle/TutorialBattle/Main/TutorialBattleEnemy.h"
#include "Battle/TutorialBattle/Main/TutorialBattlePlayer.h"
#include "Battle/TutorialBattle/UI/TutorialEnemyUI.h"
#include "Battle/Base/BeatCounter.h"
#include "Battle/TutorialBattle/Background/Heart.h"
#include "Battle/TutorialBattle/TutorialPost.h"
class TutorialBattleControl : public GameObject
{
public:
	//对象初始化函数
	virtual void Init() override;
	//更新函数
	//基于时间的更新
	virtual void Update(float ts) override;

	//调试UI渲染
	virtual void OnImGuiRender() override;


	void StartShow();


	void SetEnemyUI(std::shared_ptr<TutorialEnemyUI> enemyUI);
	void SetEnemy(std::shared_ptr<TutorialBattleEnemy> enemy);
	void SetStage(std::shared_ptr<TutorialBattleStage> stage);
	void SetPlayer(std::shared_ptr<TutorialBattlePlayer> player);

	void SetHeart(std::shared_ptr<Heart> heart);

	void SetBeatCounter(std::shared_ptr<BeatCounter> beatCounter);

	void SetPost(std::shared_ptr<TutorialPost> post);
private:
	int m_State = 0;
	int m_Bpm = 100;
	int m_Count = 0;
	GameTimer m_Awake;
	GameTimer m_Beat;
	std::shared_ptr<BeatCounter> m_BeatCounter;
	std::shared_ptr<Heart> m_Heart;
	std::shared_ptr<TutorialBattleStage> m_Stage;
	std::shared_ptr<TutorialBattleEnemy> m_Enemy;
	std::shared_ptr<TutorialBattlePlayer> m_Player;
	std::shared_ptr<TutorialEnemyUI> m_EnemyUI;

	std::shared_ptr<TutorialPost> m_Post;

};

