#pragma once
#include"Audio/SoundEngine.h"
#include "Core/Scene.h"
#include "GlobalFlag.h"
#include "GameInput.h"
#include "Transform.h"
class MapScene : public Scene
{
public:
	MapScene()
		:Scene("Map"), m_Run(4, true)
	{}
	virtual void OnAttach() override
	{
		m_Shader = Engine::Shader::Create("assets/shaders/purity.glsl");
		m_Player = Engine::Texture2DArray::Create("assets/textures/yanyan.png",3,2);
		m_Sence = Engine::Texture2DArray::Create("assets/textures/MapSence.png", 1, 1);
		m_BGM = std::make_shared<SoundSource>("assets/audio/map.wav");
		m_Camera = std::make_shared<Engine::Camera>();

		m_BGM->SetVolume(0.2f);
		m_Transform.SetPostion(glm::vec3(-1.0f, -0.5f, 0.0f));
		m_Transform.SetScale(glm::vec3(0.3f));
		m_BattleTip.SetFather(&m_Transform);
		m_BattleTip.SetPostion(glm::vec3(0.0f, 1.0f, 0.0f));
		m_Metronome.SetPostion(glm::vec3(0.0f,-0.5f,0.0f));
		m_Metronome.SetScale(glm::vec3(0.3f));
		m_Run.AutoGenerateFrames(1, 0.2f);

		SoundEngine::Play2D(m_BGM, true);
		
		
	}

	virtual void OnDetach() override
	{
	}
	virtual void OnUpdate(Engine::TimeStep ts) override
	{
		m_Time += ts;
		
		if (!GlobalFlag::InBattle())
		{
			
			m_Run.OnUpdate(ts);
			m_AnimationState = 0;
			m_Battle = false;
			float playerX = m_Transform.GetPostion().x;
			if (playerX <= 0.3f && playerX >= -0.3f)
			{
				m_Battle = true;
			}
			if (GameInput::IsKeyPoressed(RightKey))
			{
				if (!m_Foward)
				{
					m_Foward = true;
					m_Transform.SetRotation(glm::vec4(0.0f,1.0f,0.0f,glm::radians(180.0f)));
				}
				glm::vec3 pos = m_Transform.GetPostion();
				float x = pos.x + ts * m_Velocity;
				if (x > 1.4f)
					x = 1.4f;
				m_Transform.SetPostion(glm::vec3(x, pos.y, pos.z));
				m_AnimationState = 1;
				
			}
			if (GameInput::IsKeyPoressed(LeftKey))
			{
				if (m_Foward)
				{
					m_Foward = false;
					m_Transform.SetRotation(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
				}
				glm::vec3 pos = m_Transform.GetPostion();
				float x = pos.x - ts * m_Velocity;
				if (x < -1.4f)
					x = -1.4f;
				m_Transform.SetPostion(glm::vec3(x, pos.y, pos.z));
				m_AnimationState = 1;

			}
			if (GameInput::IsKeyDown(InteractiveKey))
			{
				if (m_Battle)
				{
					GlobalFlag::SetShouldInBattle(true);
				}
			}
		}




	}

	virtual void OnRender() override
	{
		if (!GlobalFlag::InBattle())
		{
			Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
			Engine::RendererCommand::Clear();
			Engine::RendererCommand::DisableDepthTest();
			m_Shader->Use();
			m_Shader->SetFloat("v_Time", m_Time);
			Engine::RendererPostProcessing::Draw();
			m_Shader->UnUse();

			
			Engine::Renderer2D::BeginScene(m_Camera, m_Sence);

			
			Engine::Renderer2D::DrawQuad(m_Metronome.GetMatrix(), glm::vec4(1.0f), 0.0f);
			

			Engine::Renderer2D::EndScene();


			Engine::Renderer2D::BeginScene(m_Camera, m_Player);

			if (m_AnimationState == 0)
				Engine::Renderer2D::DrawQuad(m_Transform.GetMatrix(), glm::vec4(1.0f), 0.0f);
			else
				Engine::Renderer2D::DrawQuad(m_Transform.GetMatrix(), glm::vec4(1.0f), m_Run.GetTexCoordZs());
			if (m_Battle)
			{
				Engine::Renderer2D::DrawQuad(m_BattleTip.GetMatrix(), glm::vec4(0.0, 1.0f, 1.0f, 1.0f), 5.0f);
			}

			Engine::Renderer2D::EndScene();
		}
		
	}
	virtual void OnImGuiRender() override
	{
	}

	void InBattle()
	{
		SoundEngine::StopAllSound(m_BGM);
	}
	void OutBattle()
	{
		SoundEngine::Play2D(m_BGM, true);
	}
private:

	bool m_Battle = false;
	bool m_Foward = false;
	float m_Velocity = 0.5f;
	Transform m_Transform;
	Transform m_BattleTip;
	Engine::Animation2D m_Run;
	float m_Time = 0;

	int m_AnimationState = 0;
	
	Transform m_Metronome;
	std::shared_ptr<Engine::Shader> m_Shader;
	

	std::shared_ptr<Engine::Texture2DArray> m_Player;
	std::shared_ptr<Engine::Texture2DArray> m_Sence;
	std::shared_ptr<Engine::Camera> m_Camera;
	std::shared_ptr<SoundSource> m_BGM;
};



