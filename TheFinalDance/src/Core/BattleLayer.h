#pragma once
#include "Engine.h"
#include "Timeline.h"
#include "Object.h"
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
	//���������ں���
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	int m_Bpm = 100;
	float m_Volume = 1.0f;

	//player
	BattlePlayer m_Player;


	glm::vec4 m_Color = glm::vec4(1.0f);


	std::shared_ptr<Timeline> m_Timeline;
	BeatCounter m_BeatCounter;

	SoundSourceLibrary m_SoundSources;
	

	std::shared_ptr<Engine::Texture2DArray> m_Texture;
	std::shared_ptr<Engine::Shader> m_BeatShader;
	
	Engine::OrthographicCamera m_Camera;
	Engine::ShaderLibrary m_ShaderLibrary;
	
};
