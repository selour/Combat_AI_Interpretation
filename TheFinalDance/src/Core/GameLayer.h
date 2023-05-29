#pragma once
#include "Engine.h"
#include "Core/Scene.h"
#include "MapSence.h"
#include "Battle/BattleScene.h"
class GameLayer :public Engine::Layer
{
public:
	GameLayer() {};
	//层生命周期函数
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
protected:
	void LayerPushScene(Scene* scene);
	void LayerPopScene(Scene* scene);
	void LayerPushOverScene(Scene* scene);
	void LayerPopOverScene(Scene* scene);
private:
	int m_FPS = 0;
	Scene* m_BattleScene = nullptr;
	MapScene* m_MapScene = nullptr;
	SceneStack m_SceneStack;

};

