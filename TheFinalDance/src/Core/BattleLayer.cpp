#include "BattleLayer.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
//-----------------------------------教程战斗----------------------------------------

bool f = true;

TutorialBattle::TutorialBattle()
	:BattleLayer("TutorialBattle"), m_Camera(1280.0f / 720.0f, 5.0f)
{}
void TutorialBattle::OnAttach()
{
	m_Bpm = 100;
	m_Volume = 1.0f;
	m_BeatCounter.SetBPM(m_Bpm);
	m_SoundSources.Load("metronome", "assets/audio/metronome.wav");
	m_SoundSources.Load("hat", "assets/audio/hat.wav");
	m_Track.addPattern("11111111", m_SoundSources.Get("metronome"));

	m_BeatShader = Engine::Shader::Create("assets/shaders/BeatShader.glsl") ;
	//m_BeatShader->SetInteger("u_Texture0", 0, true);
}

void TutorialBattle::OnDetach()
{
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{
	m_BeatCounter.SetBPM(m_Bpm);
	float bv = 60.0f / m_Bpm;
	float beatR = m_BeatCounter.GetTime() / bv;
	//计算节拍数
	m_BeatCounter.Update(ts);
	if (m_BeatCounter.GetCounter() >= 8 && !m_Track.IsPlay())
	{
		m_Track.SetState(0);
	}
	m_Track.Update(m_BeatCounter.GetCounter());

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
	{
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();

		Engine::Renderer2D::BeginScene(m_Camera, nullptr, m_BeatShader);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				Engine::Renderer2D::DrawQuad(glm::vec2(i-3, j-3), glm::vec2(0.95f), 0, m_Color, 1.0f);
			}
		}
		m_BeatShader->SetFloat("u_Radius", beatR, true);
		Engine::Renderer2D::DrawQuad(glm::vec2(0, 0), glm::vec2(3.0f), 0, glm::vec4(1.0f));
		Engine::Renderer2D::EndScene();
	}

}

void TutorialBattle::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::SliderInt("BPM", &m_Bpm, 50, 1000);
	ImGui::SliderFloat("Volume", &m_Volume, 0, 1.0f);
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::Text("beatCount:%d", m_BeatCounter.GetCounter());
	ImGui::End();

}

void TutorialBattle::OnEvent(Engine::Event& event)
{
}
