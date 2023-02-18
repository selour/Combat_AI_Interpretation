#include "BattleLayer.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
//-----------------------------------教程战斗----------------------------------------

bool f = true;

void TutorialBattle::OnAttach()
{
	m_Bpm = 100;
	m_Time = 0;
	m_Volume = 1.0f;
	m_SoundSources.Load("metronome", "assets/audio/metronome.wav");
	m_SoundSources.Load("hat", "assets/audio/hat.wav");
	m_BeatShader = Engine::Shader::Create("assets/shaders/BeatShader.glsl") ;
	//m_BeatShader->SetInteger("u_Texture0", 0, true);
}

void TutorialBattle::OnDetach()
{
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{
	float bv = 60.0f / m_Bpm;
	float beatR = m_Time / bv;
	//节拍器
	{
		//auto ss = m_SoundSources.Get("metronome");
		if (m_Time >= bv)
		{	
			//ss->SetVolume(m_Volume);
			SoundEngine::Play2D(m_SoundSources.Get("metronome"));
			//SoundEngine::Play2D(m_SoundSources.Get("hat"));
			
		}
	}
	
	if (Engine::Input::IsKeyPoressed(ENGINE_KEY_SPACE))
	{
		if (f)
		{
			SoundEngine::Play2D(m_SoundSources.Get("hat"));
			f = false;
		}
	}
	else
	{
		f = true;
	}

	
	if (m_Time >= bv)
	{
		m_Time -= bv;
	}
	m_Time += ts;


	{
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();
		Engine::Renderer2D::ResetStats();
		Engine::Renderer2D::BeginScene(m_Camera, nullptr, m_BeatShader);
		m_BeatShader->SetFloat("u_Radius", beatR, true);
		Engine::Renderer2D::DrawQuad(glm::vec2(0, 0), glm::vec2(3.0f), 0, m_Color);
		Engine::Renderer2D::EndScene();
	}

}

void TutorialBattle::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::SliderInt("BPM", &m_Bpm, 50, 1000);
	ImGui::SliderFloat("Volume", &m_Volume, 0, 1.0f);
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();

}

void TutorialBattle::OnEvent(Engine::Event& event)
{
}
