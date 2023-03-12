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

BattleStage::BattleStage(ResourceManager* resourceManager)
	:m_ResourceManager(resourceManager), m_Camera(1280.0f / 720.0f, 5.0f)
{
	m_Stage.resize(7*7);
}

void BattleStage::Start()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_Stage[i * 7 + j].Position = { i - 3, j - 3 };
			m_Stage[i * 7 + j].Awake = false;
			m_Stage[i * 7 + j].Render = false;
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
	auto shader = m_ResourceManager->GetShaderLibrary()->Get("Block");
	auto texture = m_ResourceManager->GetTextureLibrary()->Get("number");
	Engine::Renderer2D::BeginScene(m_Camera, texture, shader);
	for (int i = 0; i < m_Stage.size(); i++)
	{
		if (m_Stage[i].Render)
		{
			
			if (m_Stage[i].Step != 0)
			{
				Engine::Renderer2D::DrawQuad(m_Stage[i].Position, glm::vec2(0.95f), 0, glm::vec4(1.0f), -2.0f);
				if (m_Stage[i].Step <= 9)
				{
					Engine::Renderer2D::DrawQuad(glm::vec2(m_Stage[i].Position.x - 0.3f, m_Stage[i].Position.y + 0.3f), glm::vec2(0.25f), 0, glm::vec4(1.0f), m_Stage[i].Step);
				}
				else
				{
					int x = m_Stage[i].Step / 10;
					int y = m_Stage[i].Step % 10;
					Engine::Renderer2D::DrawQuad(glm::vec2(m_Stage[i].Position.x - 0.3f, m_Stage[i].Position.y + 0.3f), glm::vec2(0.25f), 0, glm::vec4(1.0f), x);
					Engine::Renderer2D::DrawQuad(glm::vec2(m_Stage[i].Position.x - 0.05f, m_Stage[i].Position.y + 0.3f), glm::vec2(0.25f), 0, glm::vec4(1.0f), y);
				}
					
			}
			else
			{
				Engine::Renderer2D::DrawQuad(m_Stage[i].Position, glm::vec2(0.95f), 0, glm::vec4(1.0f), -1.0f);
			}
			
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

void BattleStage::ClearStep()
{
	for (int i = 0; i < m_Stage.size(); i++)
	{
		m_Stage[i].Step = 0;

	}
}

//-----------------------------------节拍器boss-------------------------------------
TutorialBoss::TutorialBoss(const std::shared_ptr<BattleStage> stage, Engine::ParticleSystem* particleSystem, ResourceManager* resourceManager)
	:m_Stage(stage), m_ParticleSystem(particleSystem), m_ResourceManager(resourceManager), m_Camera(1280.0f / 720.0f, 5.0f)
{
}

void TutorialBoss::Start()
{
	m_Current = &m_Stage->GetStage()->at(3 * 7 + 1);
	m_Current->Awake = false;
	//设置粒子
	m_Particle.SizeBegin = 0.2f;
	m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 0.5f;
	m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Particle.VelocityVariation = glm::vec3(2.0f, 2.0f, 0.0f);
}

void TutorialBoss::Awake()
{
}
void TutorialBoss::Update(float ts)
{
	m_Position = m_Current->Position;
	m_BeatFlag.Update(ts);
	m_HitFlag.Update(ts);
	m_BeatTip.Update(ts);
	m_BeatCheck.Update(ts);
	if (m_BeatTip && m_BeatTip.GetProportion() == 1.0f)
	{
		m_BeatCheck.SetDelay(60.0f / 400.0f);
	}
}

void TutorialBoss::BufferRender()
{
}

void TutorialBoss::Render()
{
	auto shader = m_ResourceManager->GetShaderLibrary()->Get("BeatShader");
	auto texture = m_ResourceManager->GetTextureLibrary()->Get("metronome");
	float size = 0.9f;
	if (m_BeatFlag)
	{
		size += 0.15f * sin(glm::radians(m_BeatFlag.GetProportion() * 180.0f));
	}
	Engine::Renderer2D::BeginScene(m_Camera, texture, shader);
	shader->SetFloat("u_Hit", sin(glm::radians(m_HitFlag.GetProportion()*180.0f)));
	shader->SetFloat("u_Proportion", m_BeatTip.GetProportion());
	if (m_BeatTip)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.8f), 0, m_Color, -2.0f);
	}
	if (m_BeatCheck)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, m_Color, -1.0f);
	}
	else
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, glm::vec4(1.0f), -1.0f);
	}
	
	if(m_HitFlag)
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, m_Color, 0.0f);
	else
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, glm::vec4(1.0f), 0.0f);
	
	Engine::Renderer2D::EndScene();
}

void TutorialBoss::Reset()
{
}

void TutorialBoss::Destroy()
{
}

void TutorialBoss::OnBeat()
{
	if (m_IsAwake)
	{
		m_BeatFlag.SetDelay(0.15f);
	}
	
	
	if (m_BeatCount == 0)
	{
		m_BeatTip.SetDelay(60.0f / 100.f * 7.0f - 0.04f);
	}
	m_BeatCount++;
	m_BeatCount %= 8;
}

void TutorialBoss::OnHit(int step)
{

	if (m_BeatCheck)
	{
		m_HitFlag.SetDelay(60.0f / 400.0f);
		m_Particle.ColorBegin = m_Color;
		m_Particle.ColorEnd = glm::vec4(m_Color.r, m_Color.g, m_Color.b, 0.0f);
		m_Particle.Position = glm::vec3(m_Position.x, m_Position.y, 0.0f);

		for (int i = 0; i < 3; i++)
			m_ParticleSystem->Emit(m_Particle);
		SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("clap"));
	}
	else
	{
		SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("solid"));
		
	}
	
	
}



//------------------------------------玩家对象-------------------------------------

BattlePlayer::BattlePlayer(std::shared_ptr<BattleStage> stage, std::shared_ptr<TutorialBoss> boss, Engine::ParticleSystem* particleSystem, ResourceManager* resourceManager)
	:m_Stage(stage), m_Boss(boss), m_ParticleSystem(particleSystem), m_ResourceManager(resourceManager), m_Camera(1280.0f / 720.0f, 5.0f)
{

}

void BattlePlayer::Start()
{
	m_State = Free;
	m_Current = &m_Stage->GetStage()->at(3 * 7);
	//设置粒子
	m_Particle.SizeBegin = 0.2f;
	m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 0.5f;
	m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Particle.VelocityVariation = glm::vec3(8.0f, 8.0f, 0.0f);
}

void BattlePlayer::Awake()
{
}

void BattlePlayer::Update(float ts)
{
	m_Time += ts;
	m_Position = m_Current->Position;
	m_MoveFlag.Update(ts);
	m_ErrorFlag.Update(ts);
	m_BeatFlag.Update(ts);
	
	switch (m_State)
	{
	case Move:
		if (m_MoveFlag.GetProportion() == 1)
		{
			m_Current = m_Next;
			m_Position = m_Current->Position;
			m_State = Free;
		}
		else
		{
			m_Position = m_Current->Position + m_MoveFlag.GetProportion() * (m_Next->Position - m_Current->Position);
		}
		break;
	case Beat:
		if (m_MoveFlag.GetProportion() == 1)
		{
			m_State = Free;
		}
		break;
	}

	InputCheck();
		
		
}

void BattlePlayer::BufferRender()
{
}

void BattlePlayer::Render()
{
	
	auto shader = m_ResourceManager->GetShaderLibrary()->Get("BeatShader");
	auto texuture = m_ResourceManager->GetTextureLibrary()->Get("player");
	float size = 1.0f;
	if (m_BeatFlag)
	{
		size += 0.15f * sin(glm::radians(m_BeatFlag.GetProportion() * 180.0f));
	}
	Engine::Renderer2D::BeginScene(m_Camera, texuture, shader);
	shader->SetFloat("u_Proportion", m_MoveFlag.GetProportion());
	shader->SetFloat("u_Hit", 0.0f);
	//判定圈
	if (m_IsRender)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, glm::vec4(1.0f), 3.0f);
	}
	//终末拍
	if (m_State == Beat)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, m_Color, 4.0f);
	}
	//玩家图标
	if (m_ErrorFlag)
	{
		glm::vec2 pos = sin(glm::radians(m_ErrorFlag.GetProportion() * 180.0f)) * m_ErrorDirection * 0.2f;
		Engine::Renderer2D::DrawQuad(m_Position + pos, glm::vec2(size), 0, m_Color, 0.0f);
		
	}
	else
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, m_Color, 0.0f);
	}
	//判定点
	Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(0.25f), m_Time * 4, glm::vec4(1.0f, 1.0f, 1.0f, 0.8f), 1.0f);
	//错误提示
	if (m_ErrorFlag)
		Engine::Renderer2D::DrawQuad(m_Position , glm::vec2(1.5f), 0, glm::vec4(1.0f), 2.0f);
	
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
	if (m_IsAwake)
	{
		m_BeatFlag.SetDelay(0.15f);
	}
}

void BattlePlayer::InputCheck()
{
	if (!m_ErrorFlag)
	{
	
		if (GameInput::IsInteractiveKeyDown())
		{
			if (m_State == Free)
			{
				m_MoveFlag.SetDelay(60.0f / 400.0f - 0.02f);
				m_State = Beat;
				m_Step = 0;
				m_Stage->ClearStep();

				Block* boss = m_Boss->GetCurrent();
				bool flag = false;

				if (boss == m_Current->Link[0] || boss == m_Current->Link[1] ||
					boss == m_Current->Link[2] || boss == m_Current->Link[3] ||
					m_Current->Link[0] != nullptr && boss == m_Current->Link[0]->Link[3] ||
					m_Current->Link[1] != nullptr && boss == m_Current->Link[1]->Link[2] ||
					m_Current->Link[2] != nullptr && boss == m_Current->Link[2]->Link[0] ||
					m_Current->Link[3] != nullptr && boss == m_Current->Link[3]->Link[1])
				{
					m_Boss->OnHit(m_Step);
				}
				else
				{
					SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("swoosh"));
				}


				m_Particle.ColorBegin = m_Color;
				m_Particle.ColorEnd = glm::vec4(m_Color.r, m_Color.g, m_Color.b, 0.0f);
				m_Particle.Position = glm::vec3(m_Position.x, m_Position.y, 0.0f);
				for (int i = 0; i < 10; i++)
					m_ParticleSystem->Emit(m_Particle);
			}
			else
			{
				MoveError({ 0.0f , 0.0f });
			}
			
		}
		if (GameInput::IsUpKeyDown())
		{
			if (m_State == Free && m_Current->Link[3] != nullptr && m_Current->Link[3]->Awake)
			{
				MoveTo(3);
			}
			else
			{
				MoveError({ 0.0 , 1.0f });
			}
			

		}
		if (GameInput::IsDownKeyDown())
		{

			if (m_State == Free && m_Current->Link[2] != nullptr && m_Current->Link[2]->Awake)
			{
				MoveTo(2);
			}
			else
			{
				MoveError({ 0.0 , -1.0f });
			}

		}
		if (GameInput::IsLeftKeyDown())
		{

			if (m_State == Free && m_Current->Link[0] != nullptr && m_Current->Link[0]->Awake)
			{
				MoveTo(0);
			}
			else
			{
				MoveError({ -1.0f , 0.0f });
			}


		}
		if (GameInput::IsRightKeyDown())
		{

			if (m_State == Free && m_Current->Link[1] != nullptr && m_Current->Link[1]->Awake)
			{
				MoveTo(1);
			}
			else
			{
				MoveError({ 1.0f , 0.0f });
			}


		}
		
	}
}

void BattlePlayer::MoveTo(int forward)
{
	SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("hat"));
	m_Next = m_Current->Link[forward];
	m_MoveFlag.SetDelay(60.0f / 100.0f - 0.06f);
	m_State = Move;
	if (m_Current->Step == 0)
	{
		m_Step++;
		m_Current->Step = m_Step;
	}

	m_Particle.ColorBegin = glm::vec4(1.0f);
	m_Particle.ColorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	m_Particle.Position = glm::vec3(m_Position.x, m_Position.y, 0.0f);
	for (int i = 0; i < 3; i++)
		m_ParticleSystem->Emit(m_Particle);
}

void BattlePlayer::MoveError(const glm::vec2 direction)
{
	SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("error"));
	m_ErrorDirection = direction;
	m_ErrorFlag.SetDelay(60.0f / 200.0f - 0.04f);

	m_Step = 0;
	m_Stage->ClearStep();


}




//------------------------------------背景-------------------------------------
Heart::Heart(ResourceManager* resourceManager)
	:m_ResourceManager(resourceManager), m_Camera(1280.0f / 720.0f, 5.0f)
{
	Engine::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_FBO = Engine::FrameBuffer::Create(fbSpec);
}

void Heart::Start()
{
	m_IsAwake = false;
	m_IsRender = false;

}

void Heart::Awake()
{
	m_IsAwake = true;
	m_IsRender = true;
	SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("tutorial_metronome_loop"), true);
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
	auto texture = m_ResourceManager->GetTextureLibrary()->Get("heart");
	if (m_IsRender)
	{
		m_FBO->Bind();
		Engine::RendererCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		Engine::RendererCommand::Clear();
		Engine::Renderer2D::BeginScene(m_Camera, texture);
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
		auto shader = m_ResourceManager->GetShaderLibrary()->Get("heart");
		shader->SetFloat("v_Color", 0.5f + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f)), true);
		shader->SetFloat("v_Shadow", m_Beat.GetProportion());
		Engine::RendererPostProcessing::Draw(m_FBO, shader);
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
TutorialPost::TutorialPost(ResourceManager* resourceManager)
	:m_ResourceManager(resourceManager)
{
}

void TutorialPost::Start()
{
	Engine::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_FBO = Engine::FrameBuffer::Create(fbSpec);
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
	auto shader = m_ResourceManager->GetShaderLibrary()->Get("Post");
	shader->SetFloat("u_Time", m_Time, true);
	shader->SetVector2f("u_Resolution", glm::vec2(1280.0f, 720.0f));
	shader->SetFloat("u_Rhythm", sin(glm::radians(m_Rhythm.GetProportion() * 180.0f)));
	
	if (m_Noise)
	{
		shader->SetInteger("u_State", 1);
	}
	else
	{
		if (m_IsAwake)
		{
			shader->SetInteger("u_State", 2);
		}
		else
		{
			shader->SetInteger("u_State", 0);
		}
			
	}
	Engine::RendererPostProcessing::Draw(m_FBO, shader);
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
	:BattleLayer("TutorialBattle"), m_BeatCounter(&m_Objects), m_ParticleSystem(500), m_Camera(1280.0f / 720.0f, 5.0f)
{
	
}
void TutorialBattle::OnAttach()
{
	m_Bpm = 100; 
	m_Volume = 1.0f;
	m_BeatCounter.SetBPM(m_Bpm);
	//m_BeatCounter.GetTimeLine()->AddEvent(Awake, 7, 1);
	//m_BeatCounter.GetTimeLine()->AddEvent(Awake, 8, 0);
	m_Stage = std::make_shared<BattleStage>(&m_ResourceManager);
	m_Boss = std::make_shared<TutorialBoss>(m_Stage, &m_ParticleSystem,&m_ResourceManager);
	m_Player = std::make_shared<BattlePlayer>(m_Stage, m_Boss, &m_ParticleSystem, &m_ResourceManager);

	m_Objects.Add("Player", m_Player);
	m_Objects.Add("Boss", m_Boss);
	m_Objects.Add("Stage", m_Stage);

	m_Objects.Add("Heart", std::make_shared<Heart>(&m_ResourceManager));
	m_Objects.Add("Post", std::make_shared<TutorialPost>(&m_ResourceManager));


	m_ResourceManager.Init();
	m_Objects.AllObjectStart();

	//SoundEngine::Play2D( m_ResourceManager.GetSoundSourceLibrary()->Get("tutorial_metronome_start"));

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
	m_Objects.AllObjectUpdate(ts);

	m_ParticleSystem.OnUpdate(ts);


	m_Objects.AllObjectBufferRender();

	std::dynamic_pointer_cast<TutorialPost>(m_Objects.Get("Post"))->GetFBO()->Bind();
	
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();
	
	m_Objects.Get("Heart")->Render();
	
	m_Objects.Get("Stage")->Render();

	m_Objects.Get("Boss")->Render();
	m_ParticleSystem.OnRender(m_Camera);
	m_Objects.Get("Player")->Render();
	
	std::dynamic_pointer_cast<TutorialPost>(m_Objects.Get("Post"))->GetFBO()->UnBind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();

	m_Objects.Get("Post")->Render();
}

void TutorialBattle::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("%dFPS", m_FPS);
	//ImGui::SliderInt("BPM", &m_Bpm, 50, 1000);
	//ImGui::SliderFloat("Volume", &m_Volume, 0, 1.0f);
	//ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
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

//----------------------------------资源列表读入-------------------------------------
void TutorialResourceManager::Init()
{
	auto shaders = GetShaderLibrary();
	auto soundSources = GetSoundSourceLibrary();
	auto textures = GetTextureLibrary();
	shaders->Load("BeatShader", "assets/shaders/BeatShader.glsl");
	shaders->Load("Block", "assets/shaders/Block.glsl");
	shaders->Load("heart", "assets/shaders/heart.glsl");
	shaders->Load("Post", "assets/shaders/Post.glsl");
	shaders->Get("heart")->SetInteger("u_Texture0", 0, true);
	shaders->Get("Post")->SetInteger("u_Texture0", 0, true);

	soundSources->Load("tutorial_metronome_start", "assets/audio/tutorial_metronome/tutorial_metronome_start.wav");
	soundSources->Load("tutorial_metronome_loop", "assets/audio/tutorial_metronome/tutorial_metronome_loop.wav");
	soundSources->Load("hat", "assets/audio/hat.wav");
	soundSources->Load("clap", "assets/audio/clap.wav");
	soundSources->Load("swoosh", "assets/audio/swoosh.wav");
	soundSources->Load("solid", "assets/audio/solid.wav");
	soundSources->Load("error", "assets/audio/error.wav");
	soundSources->Get("hat")->SetVolume(0.2f);
	soundSources->Get("clap")->SetVolume(0.3f);
	soundSources->Get("error")->SetVolume(0.5f);

	textures->Load("number", "assets/textures/number.png", 10, 1);
	textures->Load("metronome", "assets/textures/metronome.png", 1, 1);
	textures->Load("heart", "assets/textures/heart.png", 5, 1);
	textures->Load("player", "assets/textures/player.png", 3, 1);
}