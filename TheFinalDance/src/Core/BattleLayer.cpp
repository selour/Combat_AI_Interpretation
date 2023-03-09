#include "BattleLayer.h"
#include "GameInput.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>



//--------------------------------------------------------------------------------
//-----------------------------------教程战斗--------------------------------------
//--------------------------------------------------------------------------------
// 
// 
// 
//------------------------------------战斗场地-------------------------------------
BattleStage::BattleStage()
	:m_Camera(1280.0f / 720.0f, 5.0f)
{

}

void BattleStage::Start()
{
	m_Shader = Engine::Shader::Create("assets/shaders/BeatShader.glsl");
	m_Stage.resize(7*7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_Stage[i * 7 + j].Position = { i - 3, j - 3 };
			m_Stage[i * 7 + j].Awake = true;
			m_Stage[i * 7 + j].Render = true;
			if (j > 0)
			{
				m_Stage[i * 7 + j].Link[2] = &m_Stage[i * 7 + j - 1];
			}
			if (j < 6)
			{
				m_Stage[i * 7 + j].Link[3] = &m_Stage[i * 7 + j + 1];
			}
			if (i > 0)
			{
				m_Stage[i * 7 + j].Link[0] = &m_Stage[i * 7 + j - 7];
			}
			if (i < 6)
			{
				m_Stage[i * 7 + j].Link[1] = &m_Stage[i * 7 + j + 7];
			}
		}
	}

}

void BattleStage::Awake()
{
}

void BattleStage::Update(float ts)
{
}

void BattleStage::BufferRender()
{
}

void BattleStage::Render()
{
	Engine::Renderer2D::BeginScene(m_Camera, nullptr, m_Shader);
	for (int i = 0; i < m_Stage.size(); i++)
	{
		if (m_Stage[i].Awake && m_Stage[i].Render)
		{
			Engine::Renderer2D::DrawQuad(m_Stage[i].Position, glm::vec2(0.95f), 0, glm::vec4(1.0f), 1.0f);
		}
		
	}
	Engine::Renderer2D::EndScene();
}

void BattleStage::Reset()
{
}

void BattleStage::Destroy()
{
}

void BattleStage::OnBeat()
{
}

//------------------------------------玩家对象-------------------------------------

BattlePlayer::BattlePlayer(SoundSourceLibrary* ss)
	:m_Camera(1280.0f / 720.0f, 5.0f), m_SoundSources(ss)
{
}

void BattlePlayer::Start()
{
	m_Shader = Engine::Shader::Create("assets/shaders/BeatShader.glsl");
}

void BattlePlayer::Awake()
{
}

void BattlePlayer::Update(float ts)
{
	m_Position = m_Current->Position;
	m_MoveFlag.Update(ts);
	if (!m_MoveFlag)
	{
		if (GameInput::IsUpKeyDown() && !GameInput::IsDownKeyDown() && !GameInput::IsLeftKeyDown() && !GameInput::IsRightKeyDown())
		{
			if(m_Current->Link[3] != nullptr && m_Current->Link[3]->Awake)
			{
				m_Next = m_Current->Link[3];
				m_MoveFlag.SetDelay(60.0f / 400.0f);
				SoundEngine::Play2D(m_SoundSources->Get("hat"));
			}

		}
		if (!GameInput::IsUpKeyDown() && GameInput::IsDownKeyDown() && !GameInput::IsLeftKeyDown() && !GameInput::IsRightKeyDown())
		{
			if (m_Current->Link[2] != nullptr && m_Current->Link[2]->Awake)
			{
				m_Next = m_Current->Link[2];
				m_MoveFlag.SetDelay(60.0f / 400.0f);
				SoundEngine::Play2D(m_SoundSources->Get("hat"));
			}
		}
		if (!GameInput::IsUpKeyDown() && !GameInput::IsDownKeyDown() && GameInput::IsLeftKeyDown() && !GameInput::IsRightKeyDown())
		{
			if (m_Current->Link[0] != nullptr && m_Current->Link[0]->Awake)
			{
				m_Next = m_Current->Link[0];
				m_MoveFlag.SetDelay(60.0f / 400.0f);
				SoundEngine::Play2D(m_SoundSources->Get("hat"));
			}

		}
		if (!GameInput::IsUpKeyDown() && !GameInput::IsDownKeyDown() && !GameInput::IsLeftKeyDown() && GameInput::IsRightKeyDown())
		{
			if (m_Current->Link[1] != nullptr && m_Current->Link[1]->Awake)
			{
				m_Next = m_Current->Link[1];
				m_MoveFlag.SetDelay(60.0f / 400.0f);
				SoundEngine::Play2D(m_SoundSources->Get("hat"));
			}

		}
	}
	else
	{
		if (m_MoveFlag.GetProportion() == 1)
		{
			m_Current = m_Next;
			m_Position = m_Current->Position;
		}
		else
		{
			m_Position = m_Current->Position + m_MoveFlag.GetProportion()*(m_Next->Position - m_Current->Position);
		}
		
	}

}

void BattlePlayer::BufferRender()
{
}

void BattlePlayer::Render()
{
	Engine::Renderer2D::BeginScene(m_Camera, nullptr, m_Shader);
	m_Shader->SetFloat("u_Radius", 0, true);
	Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, glm::vec4(1.0f));
	Engine::Renderer2D::EndScene();
}

void BattlePlayer::Reset()
{
}

void BattlePlayer::Destroy()
{
}

void BattlePlayer::OnBeat()
{
}

void BattlePlayer::SetBlock(Block* block)
{
	m_Current = block;
}

//------------------------------------背景-------------------------------------
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
	m_Shader->SetInteger("u_Texture0", 0, true);

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

void Heart::BufferRender()
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

	}
}


void Heart::Render()
{
	if (m_IsRender)
	{
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


//------------------------------------后期处理-------------------------------------
TutorialPost::TutorialPost()
{
}

void TutorialPost::Start()
{
	Engine::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_FBO = Engine::FrameBuffer::Create(fbSpec);

	m_Shader = Engine::Shader::Create("assets/shaders/Post.glsl");
	m_Shader->SetInteger("u_Texture0", 0, true);
}

void TutorialPost::Awake()
{
	m_IsAwake = true;
	m_Noise.SetDelay(60.0f / 100.0f);
}

void TutorialPost::Update(float ts)
{
	m_Time += ts;
	m_Noise.Update(ts);
	m_Rhythm.Update(ts);
}

void TutorialPost::BufferRender()
{

}

void TutorialPost::Render()
{
	m_Shader->SetFloat("u_Time", m_Time, true);
	m_Shader->SetVector2f("u_Resolution", glm::vec2(1280.0f, 720.0f));
	m_Shader->SetFloat("u_Rhythm", sin(glm::radians(m_Rhythm.GetProportion() * 180.0f)));
	
	if (m_Noise)
	{
		m_Shader->SetInteger("u_State", 1);
	}
	else
	{
		if (m_IsAwake)
		{
			m_Shader->SetInteger("u_State", 2);
		}
		else
		{
			m_Shader->SetInteger("u_State", 0);
		}
			
	}
	Engine::RendererPostProcessing::Draw(m_FBO, m_Shader);
}

void TutorialPost::Reset()
{
}

void TutorialPost::Destroy()
{
}

void TutorialPost::OnBeat()
{
	if (m_IsAwake)
	{
		if (m_BeatCount == 0)
		{
			m_Rhythm.SetDelay(60.0f * 8 / 100.0f);
		}
		m_BeatCount++;
		m_BeatCount %= 8;
	}
}


//------------------------------------战斗主程序-------------------------------------

TutorialBattle::TutorialBattle()
	:BattleLayer("TutorialBattle"), m_Heart(&m_SoundSources), m_Player(&m_SoundSources), m_BeatCounter(), m_Post(), m_Camera(1280.0f / 720.0f, 5.0f)
{
}
void TutorialBattle::OnAttach()
{
	m_Bpm = 100; 
	m_Volume = 1.0f;
	m_BeatCounter.SetBPM(m_Bpm);
	m_BeatCounter.AddObject(&m_Heart);
	m_BeatCounter.AddObject(&m_Post);
	m_BeatCounter.GetTimeLine()->AddObject(&m_Heart);
	m_BeatCounter.GetTimeLine()->AddObject(&m_Post);
	m_BeatCounter.GetTimeLine()->AddEvent(Awake, 7, 1);
	m_BeatCounter.GetTimeLine()->AddEvent(Awake, 8, 0);


	m_Heart.Start();
	m_BattleStage.Start();
	m_Player.Start();
	m_Player.SetBlock(&m_BattleStage.GetStage()->at(3 * 7 + 6));

	m_SoundSources.Load("tutorial_metronome_start", "assets/audio/tutorial_metronome/tutorial_metronome_start.wav");
	m_SoundSources.Load("tutorial_metronome_loop", "assets/audio/tutorial_metronome/tutorial_metronome_loop.wav");
	m_SoundSources.Load("hat", "assets/audio/hat.wav");
	m_SoundSources.Get("hat")->SetVolume(0.2f);
	m_BeatShader = Engine::Shader::Create("assets/shaders/BeatShader.glsl") ;


	m_Post.Start();

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

	m_Post.Update(ts);

	float bv = 60.0f / m_Bpm;
	
	
	m_Player.Update(ts);
	
	


	m_Heart.BufferRender();

	m_Post.GetFBO()->Bind();
	
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();
	
	m_Heart.Render();
	
	m_BattleStage.Render();

	m_Player.Render();
	
	m_Post.GetFBO()->UnBind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();

	m_Post.Render();
}

void TutorialBattle::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("%dFPS", m_FPS);
	ImGui::SliderInt("BPM", &m_Bpm, 50, 1000);
	ImGui::SliderFloat("Volume", &m_Volume, 0, 1.0f);
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::Text("beatCount:%d", int(m_BeatCounter.GetTimeLine()->GetCounter()));
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

