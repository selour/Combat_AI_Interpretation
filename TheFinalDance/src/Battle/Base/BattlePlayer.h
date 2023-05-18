#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "Core/GameInput.h"
#include "ParticleComponent.h"
#include "BattleStage.h"
#include "BattleEnemy.h"
class BattlePlayer : public GameObject
{
public:
	BattlePlayer()
	{
	}
	enum PlayerState
	{
		Free = 0, Move = 2, Beat = 3, Wait = 4
	};
	void SetStage(std::shared_ptr<BattleStage> stage)
	{
		m_Stage = stage;
	}
	void SetParticleSystem(std::shared_ptr<ParticleCompomemt> particleSystem)
	{
		m_ParticleSystem = particleSystem;
	}
	void SetEnemy(std::shared_ptr<BattleEnemy> enemy)
	{
		m_Enemy = enemy;
	}
	void SetBlock(unsigned int index)
	{
		if (m_Stage->GetBlock(m_Current))
		{
			m_Stage->GetBlock(m_Current)->Occupy = false;
		}
		if (m_State == Move)
		{
			m_Stage->GetBlock(m_Next)->Occupy = false;
			m_State = Free;
			m_MoveFlag.Clear();
		}
		m_Current = index;
		m_Stage->GetBlock(m_Current)->Occupy = true;
	}
	void SetEnable(bool enable)
	{
		m_Enable = enable;
	}
	void SetColor(glm::vec4 color)
	{
		m_Color = color;
	}
	void OnWait()
	{
		m_MoveFlag.SetTime(m_MoveTime - m_OffsetTime);
		m_State = Wait;
		m_WaitInput = None;
	}
	void ClearStep()
	{
		m_Step = 0;
		m_Stage->ClearStep();
	}
	void LostCombo()
	{
		m_ComboCount = 0;
	}
	int GetLife()
	{
		return m_Life;
	}
	int GetComboCount()
	{
		return m_ComboCount;
	}
protected:
	
	void OnRender(std::shared_ptr<Engine::Camera> camera)
	{
		auto shader = m_ObjectManager->GetShaderLibrary()->Get("BeatShader");
		auto texuture = m_ObjectManager->GetTextureLibrary()->Get("player");
		float size = 1.0f;
		
		Engine::Renderer2D::BeginScene(camera, texuture, shader);
		shader->SetFloat("u_Proportion", m_MoveFlag.GetProportion());
		shader->SetFloat("u_Hit", 0.0f);
		if(m_Enable)
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 3.0f);
		
		
		//终末拍
		if (m_State == Beat)
		{
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(3.0f), 0, m_Color, 4.0f);
		}
		//玩家图标
		if (m_ErrorFlag)
		{
			glm::vec3 pos = glm::vec3(sin(glm::radians(m_ErrorFlag.GetProportion() * 180.0f)) * m_ErrorDirection * 0.2f, 0.0f);
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
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(1.5f), 0, glm::vec4(1.0f), 2.0f);
		Engine::Renderer2D::EndScene();
	}
	void OnUpdate(float ts)
	{
		m_Position = m_Stage->GetBlock(m_Current)->Postion.GetPostion();
		m_MoveFlag.Update(ts);
		m_ErrorFlag.Update(ts);
		m_Time += ts;
		if (m_Enable)
		{
			
			
			switch (m_State)
			{
			case Move:
				if (m_MoveFlag.IsTimeOut())
				{
					m_Stage->GetBlock(m_Current)->Occupy = false;
					m_Current = m_Next;
					m_Position = m_Stage->GetBlock(m_Current)->Postion.GetPostion();
					m_State = Free;
				}
				else
				{
					m_Position = m_Stage->GetBlock(m_Current)->Postion.GetPostion() + m_MoveFlag.GetProportion() * (m_Stage->GetBlock(m_Next)->Postion.GetPostion() - m_Stage->GetBlock(m_Current)->Postion.GetPostion());
				}
				break;
			case Beat:
				if (m_MoveFlag.IsTimeOut())
				{
					m_State = Free;
				}
				break;
			case Wait:
				if (m_MoveFlag.IsTimeOut())
				{
					PlayerWaitInput();
				}
				break;
			}
			PlayerControl();
		}
	}
	void PlayerControl()
	{
		if (!m_ErrorFlag)
		{

			if (GameInput::IsKeyDown(UpKey))
			{
				if (m_State == Free && m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Up))
				{
					MoveTo(MoveForward::Up);
				}
				else
				{
					if (m_State != Wait)
					{
						MoveError({ 0.0f , 1.0f });
					}
					else
					{
						m_WaitInput = UpKey;
					}
					
				}
			}
			else
			{
				if (GameInput::IsKeyDown(DownKey))
				{
					if (m_State == Free && m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Down))
					{
						MoveTo(MoveForward::Down);
					}
					else
					{
						if (m_State != Wait)
						{
							MoveError({ 0.0f , -1.0f });
						}
						else
						{
							m_WaitInput = DownKey;
						}
					}
				}
				else
				{
					if (GameInput::IsKeyDown(LeftKey))
					{
						if (m_State == Free && m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Left))
						{
							MoveTo(MoveForward::Left);
						}
						else
						{
							if (m_State != Wait)
							{
								MoveError({ -1.0 , 0.0f });
							}
							else
							{
								m_WaitInput = LeftKey;
							}
						}
					}
					else
					{
						if (GameInput::IsKeyDown(RightKey))
						{
							if (m_State == Free && m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Right))
							{
								MoveTo(MoveForward::Right);
							}
							else
							{
								if (m_State != Wait)
								{
									MoveError({ 1.0 , 0.0f });
								}
								else
								{
									m_WaitInput = RightKey;
								}
							}
						}
						else
						{
							if (GameInput::IsKeyDown(InteractiveKey))
							{
								if (m_State == Free)
								{
									OnBeat();
								}
								else
								{
									if (m_State != Wait)
									{
										MoveError({ 0.0f , 0.0f });
									}
									else
									{
										m_WaitInput = InteractiveKey;
									}
								}
								
							}
						}
					}
				}
			}


		}
	}
	void PlayerWaitInput()
	{
		switch (m_WaitInput)
		{
		case InteractiveKey:
			OnBeat();
			break;
		case UpKey:
			if (m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Up))
			{
				MoveTo(MoveForward::Up);
			}
			else
			{
				m_State = Free;
				MoveError({ 0.0f , 1.0f });
				

			}
			break;
		case DownKey:
			if (m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Down))
			{
				MoveTo(MoveForward::Down);
			}
			else
			{
				m_State = Free;
				MoveError({ 0.0f , -1.0f });
			
			}
			break;
		case LeftKey:
			if (m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Left))
			{
				MoveTo(MoveForward::Left);
			}
			else
			{
				m_State = Free;
				MoveError({ -1.0 , 0.0f });
				
			}
			break;
		case RightKey:
			if (m_Stage->GetBlock(m_Current)->CanMove(MoveForward::Right))
			{
				MoveTo(MoveForward::Right);
			}
			else
			{
				m_State = Free;
				MoveError({ 1.0 , 0.0f });
			}
			break;
		case None:
			m_State = Free;
			break;
		default:
			break;
		}
			
			

	}
	virtual void MoveBind(){}
	virtual void ErrorBind(){}

	int m_Life = 8;
	int m_ComboCount = 0;



	float m_Time = 0.0f;
	bool m_Enable = true;
	GameTimer m_EnableFlag;
	PlayerState m_State = Free;
	InputType m_WaitInput = None;
	glm::vec4 m_Color = { 0.0f,1.0f,1.0f,1.0f };

	glm::vec3 m_Position;
	

	int m_Step = 0;
	float m_OffsetTime = 0.05f;


	GameTimer m_MoveFlag;
	float m_MoveTime = 60.0f / 100.0f;
	float m_BeatTime = 60.0f / 400.0f;
	GameTimer m_ErrorFlag;
	float m_ErrorTime = 60.0f / 200.0f;
	glm::vec2 m_ErrorDirection = { 0.0f, 0.0f };

	int m_Current = -1;;
	int  m_Next = -1;

	std::shared_ptr<BattleEnemy> m_Enemy;
	std::shared_ptr<BattleStage> m_Stage;
	std::shared_ptr<ParticleCompomemt> m_ParticleSystem;



private:
	
	void MoveTo(MoveForward forward)
	{
		m_Next = m_Stage->GetBlock(m_Current)->Link[(int)forward]->Index;
		m_Stage->GetBlock(m_Next)->Occupy = true;
		m_MoveFlag.SetTime(m_MoveTime - m_OffsetTime);
		m_State = Move;
		m_ParticleSystem->EmitParticle(3, m_Position, glm::vec3(1.0f));
		if (m_Stage->GetBlock(m_Current)->Step == 0)
		{
			m_Step++;
			m_Stage->GetBlock(m_Current)->Step = m_Step;
		}
		SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("hat"));
	}
	void MoveError(const glm::vec2 direction)
	{
		m_ErrorDirection = direction;
		m_ErrorFlag.SetTime(m_ErrorTime);
		//m_Step = 0;
		//m_Stage->ClearStep();
		SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("error"));
	}
	void ComboCount()
	{
		m_ComboCount += m_Step;
	}
	
	void OnBeat()
	{
		m_MoveFlag.SetTime(m_BeatTime - m_OffsetTime);
		m_State = Beat;
		
		m_ParticleSystem->EmitParticle(10 ,m_Position, m_Color);
		StageBlock* boss = m_Enemy->GetBlock();
		if (boss == m_Stage->GetBlock(m_Current)->Link[0] || boss == m_Stage->GetBlock(m_Current)->Link[1] ||
			boss == m_Stage->GetBlock(m_Current)->Link[2] || boss == m_Stage->GetBlock(m_Current)->Link[3] ||
			m_Stage->GetBlock(m_Current)->Link[0] != nullptr && boss == m_Stage->GetBlock(m_Current)->Link[0]->Link[3] ||
			m_Stage->GetBlock(m_Current)->Link[1] != nullptr && boss == m_Stage->GetBlock(m_Current)->Link[1]->Link[2] ||
			m_Stage->GetBlock(m_Current)->Link[2] != nullptr && boss == m_Stage->GetBlock(m_Current)->Link[2]->Link[0] ||
			m_Stage->GetBlock(m_Current)->Link[3] != nullptr && boss == m_Stage->GetBlock(m_Current)->Link[3]->Link[1])
		{
			if (m_Enemy->OnHit(m_Step))
			{
				ComboCount();
				SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("clap"));
			}
			else
			{
				LostCombo();
				SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("solid"));
			}
		}
		else
		{
			LostCombo();
			SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("swoosh"));
		}
		m_Step = 0;
		m_Stage->ClearStep();
		
	}
	
};			   