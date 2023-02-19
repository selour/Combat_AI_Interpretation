#pragma once
#include "Engine.h"
#include "AudioTrack.h"
#include "BeatCounter.h"
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
	TutorialBattle();
	//层生命周期函数
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	int m_Bpm = 100;
	float m_Volume = 1.0f;

	glm::vec4 m_Color = glm::vec4(1.0f);

	BeatCounter m_BeatCounter;

	SoundSourceLibrary m_SoundSources;
	Track m_Track;

	std::shared_ptr<Engine::Texture2DArray> m_Texture;
	std::shared_ptr<Engine::Shader> m_BeatShader;
	
	Engine::OrthographicCamera m_Camera;
	Engine::ShaderLibrary m_ShaderLibrary;
	
};
