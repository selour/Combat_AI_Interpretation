#include "BattleLayer.h"
#include "GameInput.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
//-----------------------------------�̳�ս��----------------------------------------


TutorialBattle::TutorialBattle()
	:BattleLayer("TutorialBattle"), m_Player(glm::vec2(0, -3.0f)), m_Timeline(std::make_shared<Timeline>()),m_BeatCounter(m_Timeline), m_Camera(1280.0f / 720.0f, 5.0f)
{
}
void TutorialBattle::OnAttach()
{
	m_Bpm = 100; 
	m_Volume = 1.0f;
	m_BeatCounter.SetBPM(m_Bpm);
	m_SoundSources.Load("tutorial_metronome_start", "assets/audio/tutorial_metronome/tutorial_metronome_start.wav");
	m_SoundSources.Load("tutorial_metronome_loop", "assets/audio/tutorial_metronome/tutorial_metronome_loop.wav");
	m_SoundSources.Load("hat", "assets/audio/hat.wav");
	m_SoundSources.Get("hat")->SetVolume(0.2f);
	m_BeatShader = Engine::Shader::Create("assets/shaders/BeatShader.glsl") ;
	//m_BeatShader->SetInteger("u_Texture0", 0, true);

	//auto p = m_Timeline->addPhase();
	//p->AddTracks("1", m_SoundSources.Get("metronome"));

}

void TutorialBattle::OnDetach()
{
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{
	//ʱ����£�������½�����
	m_BeatCounter.SetBPM(m_Bpm);
	//m_BeatCounter.Update(ts);
	m_Player.Update(ts);

	
	float bv = 60.0f / m_Bpm;
	float beatR = m_BeatCounter.GetTime() / bv;
	
	if (!m_Player.IsMove())
	{
		if (GameInput::IsUpKeyDown()&&!GameInput::IsDownKeyDown()&& !GameInput::IsLeftKeyDown()&& !GameInput::IsRightKeyDown())
		{
			if (m_Player.GetPos().y >= 3.0f)
			{
				m_Player.Move(BattlePlayer::MoveMode::ErrorY, 1.0f, bv / 5.0f);
			}
			else
			{
				SoundEngine::Play2D(m_SoundSources.Get("hat"));
				m_Player.Move(BattlePlayer::MoveMode::Y, 1.0f, bv / 5.0f);
			}
			
		}
		if (!GameInput::IsUpKeyDown() && GameInput::IsDownKeyDown() && !GameInput::IsLeftKeyDown() && !GameInput::IsRightKeyDown())
		{
			if (m_Player.GetPos().y <= -3.0f)
			{
				m_Player.Move(BattlePlayer::MoveMode::ErrorY, -1.0f, bv / 5.0f);
			}
			else
			{ 
				SoundEngine::Play2D(m_SoundSources.Get("hat"));
				m_Player.Move(BattlePlayer::MoveMode::Y, -1.0f, bv / 5.0f);
			}
		}
		if (!GameInput::IsUpKeyDown() && !GameInput::IsDownKeyDown() && GameInput::IsLeftKeyDown() && !GameInput::IsRightKeyDown())
		{
			if (m_Player.GetPos().x <= -3.0f)
			{
				m_Player.Move(BattlePlayer::MoveMode::ErrorX, -1.0f, bv / 5.0f);
			}
			else
			{
				SoundEngine::Play2D(m_SoundSources.Get("hat"));
				m_Player.Move(BattlePlayer::MoveMode::X, -1.0f, bv / 5.0f);
			}
			
		}
		if (!GameInput::IsUpKeyDown() && !GameInput::IsDownKeyDown() && !GameInput::IsLeftKeyDown() && GameInput::IsRightKeyDown())
		{
			if (m_Player.GetPos().x >= 3.0f)
			{
				m_Player.Move(BattlePlayer::MoveMode::ErrorX, 1.0f, bv / 5.0f);
			}
			else
			{
				SoundEngine::Play2D(m_SoundSources.Get("hat"));
				m_Player.Move(BattlePlayer::MoveMode::X, 1.0f, bv / 5.0f);
			}
			
		}
	}
	


	GameInput::UpdateKeyEvent();

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
		Engine::Renderer2D::DrawQuad(m_Player.GetPos(), glm::vec2(3.0f), 0, glm::vec4(1.0f));
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
	ImGui::Text("Pos:%.1f,%.1f", m_Player.GetPos().x, m_Player.GetPos().y);
	ImGui::End();

}

void TutorialBattle::OnEvent(Engine::Event& event)
{
}
