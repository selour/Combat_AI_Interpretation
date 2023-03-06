#pragma once
#include "Engine.h"
#include "Audio/SoundEngine.h"
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

class Heart : public Object
{
public:
	Heart();
	virtual void Start() override;
	virtual void Update(float ts) override;
	virtual void Render()override;
	virtual void Reset() override;
	virtual void Destroy() override;


	virtual void OnBeat() override;

	float* GetPos1()
	{
		return &m_Postion1.x;
	}
	float* GetPos2()
	{
		return &m_Postion2.x;
	}
	float* GetPos3()
	{
		return &m_Postion3.x;
	}
	float* GetPos4()
	{
		return &m_Postion4.x;
	}
	float* GetPos5()
	{
		return &m_Postion5.x;
	}
	float* GetSize()
	{
		return &m_Size;
	}

private:
	glm::vec2 m_Postion1 = { 0.045f, -0.571f };
	glm::vec2 m_Postion2 = { -0.711f, 0.044f };
	glm::vec2 m_Postion3 = { 0.4f, 0.22f };
	glm::vec2 m_Postion4 = { 0.177f, 0.7f };
	glm::vec2 m_Postion5 = { -0.356f, 0.747f };
	float m_Size = 1.3f;

	DelaySwitch m_Beat;

	std::shared_ptr<Engine::Texture2DArray> m_Texture;
	Engine::OrthographicCamera m_Camera;
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
	//背景板
	Heart m_Heart;
	

	//player
	BattlePlayer m_Player;

	glm::vec4 m_Color = glm::vec4(1.0f);


	BeatCounter m_BeatCounter;

	SoundSourceLibrary m_SoundSources;
	

	//std::shared_ptr<Engine::Texture2DArray> m_Texture;
	std::shared_ptr<Engine::Shader> m_BeatShader;
	
	Engine::OrthographicCamera m_Camera;
	Engine::ShaderLibrary m_ShaderLibrary;
	
};
