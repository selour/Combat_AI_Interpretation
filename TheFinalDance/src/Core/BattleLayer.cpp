#include "BattleLayer.h"
#include "GameInput.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>



//--------------------------------------------------------------------------------
//-----------------------------------�̳�ս��--------------------------------------
//--------------------------------------------------------------------------------


//ʱ�����¼��ύ����
#pragma region �¼�
//����������λ����boss��һ�λ��д���
void StartUp(EventQueue* eventQueue)
{
	eventQueue->Emit("Start", EventType::Awake);
	eventQueue->Emit("BeatControl", EventType::Change);
	eventQueue->Emit("Camera", EventType::Trigger);
	eventQueue->Emit("Player", EventType::DisEnable);
}
//��ʼ�ؿ�������̨������д���
void StartLevel(EventQueue* eventQueue)
{
	eventQueue->Emit("Player", EventType::Awake);
	eventQueue->Emit("Boss", EventType::Awake);
	eventQueue->Emit("Stage", EventType::Awake);
	eventQueue->Emit("BeatCounter", EventType::Reset);
	eventQueue->Emit("Player", EventType::Enable);
	eventQueue->Emit("Music", EventType::Awake);
}
//������Ͻ׶�,�����ֿ����д���
void GlitchState(EventQueue* eventQueue)
{
	eventQueue->Emit("Heart", EventType::Awake);
	eventQueue->Emit("Post", EventType::Awake);
	eventQueue->Emit("Player", EventType::Change);
}


#pragma endregion
//------------------------------------ս������-------------------------------------
#pragma region ս������
void BattleStage::Init()
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
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_Stage[i * 7 + j].Awake = true;
			m_Stage[i * 7 + j].Render = true;
			
		}
	}
	m_AwakeFlag.SetDelay(60.0f / 100.0f);
}

void BattleStage::Update(float ts)
{
	m_AwakeFlag.Update(ts);
}


void BattleStage::Render()
{
	auto shader = m_ResourceManager->GetShaderLibrary()->Get("Block");
	auto texture = m_ResourceManager->GetTextureLibrary()->Get("number");
	float alpha = 1.0f;
	if (m_AwakeFlag)
	{
		alpha = m_AwakeFlag;
	}
	Engine::Renderer2D::BeginScene(*m_Camera, texture, shader);
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
				Engine::Renderer2D::DrawQuad(m_Stage[i].Position, glm::vec2(0.95f), 0, glm::vec4(1.0f, 1.0f, 1.0f, alpha), -1.0f);
			}
			
		}
			
	}
	Engine::Renderer2D::EndScene();
}


void BattleStage::ClearStep()
{
	for (int i = 0; i < m_Stage.size(); i++)
	{
		m_Stage[i].Step = 0;

	}
}
#pragma endregion
//-----------------------------------������boss-------------------------------------
#pragma region Boss

void TutorialBoss::Init()
{
	m_Current = &m_Stage->GetStage()->at(3 * 7 + 1);
	m_Current->Awake = false;
	//��������
	m_Particle.SizeBegin = 0.2f;
	m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 0.5f;
	m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Particle.VelocityVariation = glm::vec3(2.0f, 2.0f, 0.0f);
}
void TutorialBoss::Awake()
{
	m_IsAwake = true;
	m_Current = &m_Stage->GetStage()->at(3 * 7 + 1);
	m_Current->Awake = false;
}
void TutorialBoss::Trigger()
{
	m_BeatTip.SetDelay(60.0f / 100.0f * 7.0f);
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


void TutorialBoss::OnBeat()
{
	if (m_IsAwake)
	{
		m_BeatFlag.SetDelay(0.15f);
	}
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
	Engine::Renderer2D::BeginScene(*m_Camera, texture, shader);
	
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
	
	if (m_HitFlag)
	{
		float random = Engine::Random::Float();
		shader->SetFloat("u_Hit", random);
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, m_Color, 0.0f);
	}
	else
	{
		
		shader->SetFloat("u_Hit", 0.0f);
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, glm::vec4(1.0f), 0.0f);
	}
	Engine::Renderer2D::EndScene();
}


void TutorialBoss::OnHit(int step)
{

	if (m_BeatCheck)
	{
		if (!m_FirstHit)
		{
			StartUp(m_EventQueue);
			m_FirstHit = true;
			m_HitFlag.SetDelay(3.0f);
			SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("bell"));
		}
		else
		{
			m_HitFlag.SetDelay(60.0f / 400.0f);
			
		} 
		SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("clap"));
			
		m_Particle.ColorBegin = m_Color;
		m_Particle.ColorEnd = glm::vec4(m_Color.r, m_Color.g, m_Color.b, 0.0f);
		m_Particle.Position = glm::vec3(m_Position.x, m_Position.y, 0.0f);
		for (int i = 0; i < 3; i++)
			m_ParticleSystem->Emit(m_Particle);
		
	}
	else
	{
		SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("solid"));
		
	}
	
	
}

#pragma endregion
//------------------------------------��Ҷ���-------------------------------------
#pragma region ���
void BattlePlayer::Init()
{
	m_State = Free;
	m_Current = &m_Stage->GetStage()->at(3 * 7);
	//��������
	m_Particle.SizeBegin = 0.2f;
	m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 0.5f;
	m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Particle.VelocityVariation = glm::vec3(8.0f, 8.0f, 0.0f);
}

void BattlePlayer::Awake()
{
	m_IsAwake = true;

	m_AwakeFlag.SetDelay(60.0f / 100.0f);
	m_Next = m_Current;
	m_MoveFlag.SetDelay(60.0f / 100.0f - 0.06f);
	m_State = Move;
}

void BattlePlayer::Enable()
{
	m_Enable = true;
}

void BattlePlayer::DisEnable()
{
	m_Enable = false;
}

void BattlePlayer::Update(float ts)
{
	m_Time += ts;
	m_Position = m_Current->Position;
	m_MoveFlag.Update(ts);
	m_ErrorFlag.Update(ts);
	m_BeatFlag.Update(ts);
	m_AwakeFlag.Update(ts);

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
	if (m_Enable)
	{
		InputCheck();
	}
	
		
		
}

void BattlePlayer::OnBeat()
{
	if (m_IsAwake)
	{
		m_BeatFlag.SetDelay(0.15f);
	}
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
	float alpha = 1.0f;
	if (m_AwakeFlag)
	{
		float alpha = m_AwakeFlag;
	}
	Engine::Renderer2D::BeginScene(*m_Camera, texuture, shader);
	shader->SetFloat("u_Proportion", m_MoveFlag.GetProportion());
	shader->SetFloat("u_Hit", 0.0f);
	//�ж�Ȧ
	if (m_IsAwake)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, glm::vec4(1.0f, 1.0f, 1.0f, alpha), 3.0f);
	}
	//��ĩ��
	if (m_State == Beat)
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, m_Color, 4.0f);
	}
	//���ͼ��
	if (m_ErrorFlag)
	{
		glm::vec2 pos = sin(glm::radians(m_ErrorFlag.GetProportion() * 180.0f)) * m_ErrorDirection * 0.2f;
		Engine::Renderer2D::DrawQuad(m_Position + pos, glm::vec2(size), 0, m_Color, 0.0f);
		
	}
	else
	{
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(size), 0, m_Color, 0.0f);
	}
	//�ж���
	Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(0.25f), m_Time * 4, glm::vec4(1.0f, 1.0f, 1.0f, 0.8f), 1.0f);
	//������ʾ
	if (m_ErrorFlag)
		Engine::Renderer2D::DrawQuad(m_Position , glm::vec2(1.5f), 0, glm::vec4(1.0f), 2.0f);
	
	Engine::Renderer2D::EndScene();
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




#pragma endregion
//------------------------------------����������-------------------------------------
#pragma region ����������
void Heart::Init()
{
	m_IsAwake = false;
	m_IsRender = false;

}

void Heart::Awake()
{
	m_IsAwake = true;
	m_IsRender = true;
}


void Heart::Update(float ts)
{
	if (m_IsAwake)
	{
		m_Beat.Update(ts);
	}
	
}
void Heart::OnBeat()
{
	if (m_IsAwake)
	{
		m_Beat.SetDelay(0.15f);
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

		Engine::Renderer2D::BeginScene(*m_Camera, texture);
		if (m_Beat)
		{
			for (int i = 0; i < 5; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Postion[i], glm::vec2(m_Size + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f))), 0, glm::vec4(1.0f), float(i));
			}

		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Postion[i], glm::vec2(m_Size), 0, glm::vec4(1.0f), float(i));
			}
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
#pragma endregion
//------------------------------------���ڴ���-------------------------------------
#pragma region ���ڴ���
void TutorialPost::Init()
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
	if (m_IsAwake)
	{
		m_Time += ts;
		m_Noise.Update(ts);
		m_Rhythm.Update(ts);
	}
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
#pragma endregion
//---------------------------------��̨���������-------------------------
#pragma region ��̨���������
void TutorialCameraControl::Trigger()
{
	m_IsAwake = true;
	m_DelayIn.SetDelay(0.2f);
}
void TutorialCameraControl::Update(float ts)
{
	if(m_IsAwake)
	{
		m_Focus.Update(ts);
		m_DelayIn.Update(ts);
		m_DelayOut.Update(ts); 


		if (m_DelayIn)
		{
			auto pos = m_Pos + (m_FocusPos - m_Pos) * (float)m_DelayIn;
			float zoom = m_ZoomLevel + (m_FocusZoomLevel - m_ZoomLevel) * (float)m_DelayIn;
			m_Camera->SetPosition(glm::vec3(pos.x, pos.y, 0.0f));
			m_Camera->SetProjection(1280.0f / 720.0f, zoom);
			if (m_DelayIn.GetProportion() == 1.0f)
			{
				m_Focus.SetDelay(2.0f);
			}
			
		}
		if (m_Focus.IsEnd())
		{
			m_DelayOut.SetDelay(2.0f);
		}

		if (m_DelayOut)
		{
			auto pos = m_FocusPos + (m_Pos - m_FocusPos) * (float)m_DelayOut;
			float zoom = m_FocusZoomLevel + (m_ZoomLevel - m_FocusZoomLevel) * (float)m_DelayOut;
			m_Camera->SetPosition(glm::vec3(pos.x, pos.y, 0.0f));
			m_Camera->SetProjection(1280.0f / 720.0f, zoom);

			if (m_DelayOut.GetProportion() == 1.0f)
			{
				m_IsAwake = false;
				StartLevel(m_EventQueue);
			}
		}
	}
}
#pragma endregion
//------------------------------------�ж�Ȧ����---------------------------------
#pragma region �ж�Ȧ����
void TutorialBeatControl::Change()
{
	m_State++;
}
void TutorialBeatControl::OnBeat()
{
	if (!m_IsAwake)
	{
		switch (m_State)
		{
		case 0:
			if(m_BeatCount == 0)
				m_EventQueue->Emit(ObjectEvent("Boss", EventType::Trigger));
			m_BeatCount++;
			m_BeatCount %= 8;
			break;
		}
		
	}
}
#pragma endregion
//--------------------------------------��������----------------------------------
#pragma region ��������
void TutorialStartUp::Awake()
{
	m_IsAwake = true;
	m_Delay.SetDelay(1.5f);
}

void TutorialStartUp::Update(float ts)
{
	if (m_IsAwake)
	{
		m_Delay.Update(ts);
		if (m_Delay.IsEnd())
		{
			SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("ddddance"));
		}
	}
}
#pragma endregion
//---------------------------------------���ֿ���-------------------------------
#pragma region ���ֿ���
void TutorialMusic::Awake()
{
	m_Delay.SetDelay(60.0f / 100.0f);
}

void TutorialMusic::Update(float ts)
{
	m_Delay.Update(ts);

	if (m_Delay.IsEnd())
	{
		m_IsAwake = true;
		SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("tutorial_metronome_start"));
	}
}
void TutorialMusic::OnBeat()
{
	if (m_IsAwake)
	{
		m_BeatCount++;
		if (m_BeatCount == 15)
		{
			SoundEngine::Play2D(m_ResourceManager->GetSoundSourceLibrary()->Get("tutorial_metronome_loop"), true);
			GlitchState(m_EventQueue);
		}
	}
}
#pragma endregion

//------------------------------------ս��������-------------------------------------
#pragma region ս��������
TutorialBattle::TutorialBattle()
	:BattleLayer("TutorialBattle"), m_EventQueue(&m_Objects), m_ParticleSystem(500), m_Camera(1280.0f / 720.0f, 5.0f)
{
	
}
void TutorialBattle::OnAttach()
{

	std::shared_ptr<BeatCounter> beatCounter = std::make_shared<BeatCounter>(&m_Objects);
	beatCounter->SetBPM(100);

	auto player = std::make_shared<BattlePlayer>();
	auto boss = std::make_shared<TutorialBoss>();
	auto stage = std::make_shared<BattleStage>();
	auto heart = std::make_shared<Heart>();

	auto camera = std::make_shared<TutorialCameraControl>();
	player->SetBoss(boss);
	player->SetStage(stage);
	player->SetCamera(&m_Camera);
	boss->SetStage(stage);
	boss->SetCamera(&m_Camera);
	stage->SetCamera(&m_Camera);
	heart->SetCamera(&m_Camera);
	camera->SetCamera(&m_Camera);

	m_Objects.Add("BeatCounter", beatCounter);
	
	m_Objects.Add("Player", player);
	m_Objects.Add("Boss", boss);
	m_Objects.Add("Stage", stage);

	m_Objects.Add("Heart", heart);
	m_Objects.Add("Post", std::make_shared<TutorialPost>());

	m_Objects.Add("Camera", camera);
	m_Objects.Add("BeatControl", std::make_shared<TutorialBeatControl>());
	m_Objects.Add("Start", std::make_shared<TutorialStartUp>());
	m_Objects.Add("Music", std::make_shared<TutorialMusic>());
	m_ResourceManager.Init();

	m_Objects.AllObjectSetEventQueue(&m_EventQueue);
	m_Objects.AllObjectSetResourceManager(&m_ResourceManager);
	m_Objects.AllObjectSetParticleSystem(&m_ParticleSystem);

	m_Objects.AllObjectInit();
	beatCounter->Awake();

	//StartUp(&m_EventQueue);
	
	
	//StartLevel(&m_EventQueue);
	
	//GlitchState(&m_EventQueue);
	


}

void TutorialBattle::OnDetach()
{
}

void TutorialBattle::OnUpdate(Engine::TimeStep ts)
{
	//�߼�����
	m_FPS = int(1.0f / ts);
	m_Objects.AllObjectUpdate(ts);

	m_ParticleSystem.OnUpdate(ts);




	//�¼�����
	m_EventQueue.OnUpdate();

	//��Ⱦ����
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
	//ImGui::DragFloat2("Position", &m_Position.x, 0.1f, -5.0f, 5.0f);
	//ImGui::DragFloat("ZoomLevel", &m_ZoomLevel, 0.1f, 0.0f, 5.0f);
	ImGui::End();
}

void TutorialBattle::OnEvent(Engine::Event& event)
{
}
#pragma endregion
//----------------------------------��Դ�б����-------------------------------------
#pragma region ��Դ
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
	soundSources->Load("bell", "assets/audio/tutorial_metronome/Bell.wav");
	soundSources->Load("ddddance", "assets/audio/ddddance_time.wav");
	soundSources->Load("hat", "assets/audio/hat.wav");
	soundSources->Load("clap", "assets/audio/clap.wav");
	soundSources->Load("swoosh", "assets/audio/swoosh.wav");
	soundSources->Load("solid", "assets/audio/solid.wav");
	soundSources->Load("error", "assets/audio/error.wav");
	soundSources->Get("bell")->SetVolume(0.5f);
	soundSources->Get("ddddance")->SetVolume(0.5f);
	soundSources->Get("hat")->SetVolume(0.2f); 
	soundSources->Get("clap")->SetVolume(0.3f);
	soundSources->Get("error")->SetVolume(0.5f);

	textures->Load("number", "assets/textures/number.png", 10, 1);
	textures->Load("metronome", "assets/textures/metronome.png", 1, 1);
	textures->Load("heart", "assets/textures/heart.png", 5, 1);
	textures->Load("player", "assets/textures/player.png", 3, 1);
}
#pragma endregion


