#pragma once
#include "Core/ObjectManager.h"
#include "Core/GameTimer.h"
#include "Core/GameInput.h"
#include "BattleStage.h"
class BattlePlayer : public GameObject
{
public:
	BattlePlayer()
	{

	}
	enum PlayerState
	{
		Free = 0, Move = 2, Beat = 3
	};
	void SetStage(std::shared_ptr<BattleStage> stage)
	{
		m_Stage = stage;
	}
	void SetInitBlock(StageBlock* block)
	{
		m_Current = block;
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
		//判定圈

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
		m_Time += ts;
		m_Position = m_Current->Postion.GetPostion();
		m_MoveFlag.Update(ts);
		m_ErrorFlag.Update(ts);
		switch (m_State)
		{
		case Move:
			if (m_MoveFlag.IsTimeOut())
			{
				m_Current = m_Next;
				m_Position = m_Current->Postion.GetPostion();
				m_State = Free;
			}
			else
			{
				m_Position = m_Current->Postion.GetPostion() + m_MoveFlag.GetProportion() * (m_Next->Postion.GetPostion() - m_Current->Postion.GetPostion());
			}
			break;
		case Beat:
			if (m_MoveFlag.IsTimeOut())
			{
				m_State = Free;
			}
			break;
		}
		
	}
	void PlayerControl()
	{
		if (m_Enable && !m_ErrorFlag)
		{

			if (GameInput::IsKeyDown(UpKey))
			{
				if (m_State == Free && m_Current->CanMove(MoveForward::Up))
				{
					MoveTo(MoveForward::Up);
				}
				else
				{
					MoveError({ 0.0f , 1.0f });
				}
			}
			else
			{
				if (GameInput::IsKeyDown(DownKey))
				{
					if (m_State == Free && m_Current->CanMove(MoveForward::Down))
					{
						MoveTo(MoveForward::Down);
					}
					else
					{
						MoveError({ 0.0f , -1.0f });
					}
				}
				else
				{
					if (GameInput::IsKeyDown(LeftKey))
					{
						if (m_State == Free && m_Current->CanMove(MoveForward::Left))
						{
							MoveTo(MoveForward::Left);
						}
						else
						{
							MoveError({ -1.0 , 0.0f });
						}
					}
					else
					{
						if (GameInput::IsKeyDown(RightKey))
						{
							if (m_State == Free && m_Current->CanMove(MoveForward::Right))
							{
								MoveTo(MoveForward::Right);
							}
							else
							{
								MoveError({ 1.0 , 0.0f });
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
									MoveError({ 0.0f , 0.0f });
								}
								
							}
						}
					}
				}
			}


		}
	}
	virtual void MoveBind(){}
	virtual void ErrorBind(){}
	float m_Time = 0.0f;
	bool m_Enable = true;
	PlayerState m_State = Free;

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

	StageBlock* m_Current = nullptr;
	StageBlock* m_Next = nullptr;

	std::shared_ptr<BattleStage> m_Stage;
private:
	
	void MoveTo(MoveForward forward)
	{
		m_Next = m_Current->Link[(int)forward];
		m_MoveFlag.SetTime(m_MoveTime - m_OffsetTime);
		m_State = Move;
		if (m_Current->Step == 0)
		{
			m_Step++;
			m_Current->Step = m_Step;
		}
		SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("hat"));
		MoveBind();
	}
	void MoveError(const glm::vec2 direction)
	{
		m_ErrorDirection = direction;
		m_ErrorFlag.SetTime(m_ErrorTime);
		//m_Step = 0;
		//m_Stage->ClearStep();
		SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("error"));
		ErrorBind();
	}
	void OnBeat()
	{
		m_MoveFlag.SetTime(m_BeatTime - m_OffsetTime);
		m_State = Beat;
		m_Step = 0;
		m_Stage->ClearStep();
		SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("swoosh"));
	}
};			   