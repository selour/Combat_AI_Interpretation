#pragma once
#include "Engine/Core/Layer.h"
#include "Engine/Core/Core.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Events/Event.h"
#include <irrKlang.h>
#include <memory>
class BattleLayer :public Engine::Layer
{
public:
	BattleLayer(const std::string& name)
		:Layer(name)
	{}
};
class TutorialBattle : public BattleLayer
{
public:
	TutorialBattle()
		:BattleLayer("TutorialBattle")
	{}
	//层生命周期函数
	virtual void OnAttach() override;
	virtual void OnDetach() {}
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() {}
	virtual void OnEvent(Engine::Event& event) {}
private:
	unsigned int m_Bpm;
	float m_time;
	irrklang::ISoundEngine* SoundEngine;

};
