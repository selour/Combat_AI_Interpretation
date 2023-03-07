#include "BattleLayer.h"
#include "GameInput.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>




//-----------------------------------教程战斗----------------------------------------




Heart::Heart(SoundSourceLibrary* ss)
	:m_Camera(1280.0f / 720.0f, 5.0f),m_SoundSources(ss)
{
}

void Heart::Start()
{
	m_Texture = Engine::Texture2DArray::Create("assets/textures/heart.png", 5, 1);
	Engine::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_FBO = Engine::FrameBuffer::Create(fbSpec);

	m_Shader = Engine::Shader::Create("assets/shaders/heart.glsl");
}

void Heart::Awake()
{
	m_IsAwake = true;
	m_IsRender = true;
	SoundEngine::Play2D(m_SoundSources->Get("tutorial_metronome_loop"), true);
}


void Heart::Update(float ts)
{
	if (m_IsAwake)
	{
		m_Beat.Update(ts);
	}
	
}


void Heart::Render()
{
	if (m_IsRender)
	{
		m_FBO->Bind();
		Engine::RendererCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		Engine::RendererCommand::Clear();
		Engine::Renderer2D::BeginScene(m_Camera, m_Texture);
		if (m_Beat)
		{
			Engine::Renderer2D::DrawQuad(m_Postion1, glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), 0.0f);
			Engine::Renderer2D::DrawQuad(m_Postion2, glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), 1.0f);
			Engine::Renderer2D::DrawQuad(m_Postion3, glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), 2.0f);
			Engine::Renderer2D::DrawQuad(m_Postion4, glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), 3.0f);
			Engine::Renderer2D::DrawQuad(m_Postion5, glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), 4.0f);
		}
		else
		{
			Engine::Renderer2D::DrawQuad(m_Postion1, glm::vec2(m_Size), 0, glm::vec4(1.0f), 0.0f);
			Engine::Renderer2D::DrawQuad(m_Postion2, glm::vec2(m_Size), 0, glm::vec4(1.0f), 1.0f);
			Engine::Renderer2D::DrawQuad(m_Postion3, glm::vec2(m_Size), 0, glm::vec4(1.0f), 2.0f);
			Engine::Renderer2D::DrawQuad(m_Postion4, glm::vec2(m_Size), 0, glm::vec4(1.0f), 3.0f);
			Engine::Renderer2D::DrawQuad(m_Postion5, glm::vec2(m_Size), 0, glm::vec4(1.0f), 4.0f);
		}
		Engine::Renderer2D::EndScene();
		m_FBO->UnBind();
		
		m_Shader->SetFloat("v_Color", 0.5f + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f)), true);
		m_Shader->SetFloat("v_Shadow", m_Beat.GetProportion());
		Engine::RendererPostProcessing::Draw(m_FBO, m_Shader);
	}
	
}

void Heart::Reset()
{
}

void Heart::Destroy()
{
}

void Heart::OnBeat()
{
	m_Beat.SetDelay(0.15f);
}

TutorialBattle::TutorialBattle()
	:BattleLayer("TutorialBattle"), m_Heart(&m_SoundSources), m_Player(glm::vec2(0, -3.0f)), m_BeatCounter(), m_Camera(1280.0f / 720.0f, 5.0f)
{
}
void TutorialBattle::OnAttach()
{
	m_Bpm = 100; 
	m_Volume = 1.0f;
	m_BeatCounter.SetBPM(m_Bpm);
	m_BeatCounter.AddObject(&m_Heart);
	m_BeatCounter.GetTimeLine()->AddObject(&m_Heart);
	m_BeatCounter.GetTimeLine()->AddEvent(Awake, 8, 0);

	m_Heart.Start();
	m_SoundSources.Load("tutorial_metronome_start", "assets/audio/tutorial_metronome/tutorial_metronome_start.wav");
	m_SoundSources.Load("tutorial_metronome_loop", "assets/audio/tutorial_metronome/tutorial_metronome_loop.wav");
	m_SoundSources.Load("hat", "assets/audio/hat.wav");
	m_SoundSources.Get("hat")->SetVolume(0.2f);
	m_BeatShader = Engine::Shader::Create("assets/shaders/BeatShader.glsl") ;
	//m_BeatShader->SetInteger("u_Texture0", 0, true);

	//auto p = m_Timeline->addPhase();
	//p->AddTracks("1", m_SoundSources.Get("metronome"));
	SoundEngine::Play2D(m_SoundSources.Get("tutorial_metronome_start"));

}

void TutorialBattle::OnDetach()
{
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{
	m_FPS = int(1.0f / ts);
	//时间更新，计算更新节拍数
	m_BeatCounter.SetBPM(m_Bpm);
	m_BeatCounter.Update(ts);
	m_Player.Update(ts);

	m_Heart.Update(ts);
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
		Engine::RendererCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		Engine::RendererCommand::Clear();
		Engine::RendererPostProcessing::Draw(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		m_Heart.Render();
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
	ImGui::Text("%dFPS", m_FPS);
	ImGui::SliderInt("BPM", &m_Bpm, 50, 1000);
	ImGui::SliderFloat("Volume", &m_Volume, 0, 1.0f);
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::Text("beatCount:%d", int(m_BeatCounter.GetTimeLine()->GetCounter()));
	ImGui::Text("Pos:%.1f,%.1f", m_Player.GetPos().x, m_Player.GetPos().y);
	ImGui::End();
	/*
	ImGui::Begin("Heart Settings");
	ImGui::SliderFloat2("Postion1", m_Heart.GetPos1(), -2.0f, 2.0f);
	ImGui::SliderFloat2("Postion2", m_Heart.GetPos2(), -2.0f, 2.0f);
	ImGui::SliderFloat2("Postion3", m_Heart.GetPos3(), -2.0f, 2.0f);
	ImGui::SliderFloat2("Postion4", m_Heart.GetPos4(), -2.0f, 2.0f);
	ImGui::SliderFloat2("Postion5", m_Heart.GetPos5(), -2.0f, 2.0f);
	ImGui::SliderFloat("Size", m_Heart.GetSize(), 0.0f, 5.0f);
	ImGui::End();
	*/
}

void TutorialBattle::OnEvent(Engine::Event& event)
{
}

