#pragma once
#include "Engine.h"
#include "SoundEngine.h"
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
		:BattleLayer("TutorialBattle"), m_Camera(1280.0f / 720.0f, 10.0f)
	{}
	//层生命周期函数
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	int m_Bpm = 100;
	float m_Time = 0.0f;
	float m_Volume = 1.0f;

	glm::vec4 m_Color = glm::vec4(1.0f);

	std::shared_ptr<Engine::Shader> m_BeatShader;

	SoundSourceLibrary m_SoundSources;
	Engine::OrthographicCamera m_Camera;
	Engine::ShaderLibrary m_ShaderLibrary;
};
