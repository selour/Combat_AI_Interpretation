#include "TutorialEnemyUI.h"
#include <imgui.h>
TutorialEnemyUI::TutorialEnemyUI()
{
	
	m_Panel.SetFather(&m_Character);
	m_PanelBloom.SetFather(&m_Character);
	m_Pointer.SetFather(&m_Character);
	m_Base.SetFather(&m_Character);
	m_Knob.SetFather(&m_Character);

	m_RotationPoint.SetFather(&m_Pointer);

	m_PointerPole.SetFather(&m_RotationPoint);
	m_PointerBloom.SetFather(&m_RotationPoint);

	m_LifeSlot.SetFather(&m_Frame);
	m_LifeSlot.SetPostion(glm::vec3(-0.324f, -0.16f, 0.1f));
	m_LifeSlot.SetScale(glm::vec3(0.1f, 0.4f, 1.0f));

	for (int i = 0; i < 20; i++)
	{
		m_Slot[i].SetFather(&m_LifeSlot);
		float pos = -0.475f + i * 0.05f;
		m_Slot[i].SetPostion(glm::vec3(0.0f, pos, 1.0f));
		m_Slot[i].SetScale(glm::vec3(0.9f, 0.03f, 1.0f));
		
	}

	m_Main.SetPostion(glm::vec3(1.28f, 0.0f , 0.0f));
	m_Main.SetScale(glm::vec3(0.9f));
	m_Background.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_Character.SetPostion(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Panel.SetPostion(glm::vec3(0.0f, 0.0f, 0.1f));
	m_Panel.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_PanelBloom.SetPostion(glm::vec3(0.0f, 0.0f, 0.2f));
	m_PanelBloom.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));

	m_Pointer.SetPostion(glm::vec3(0.0f, -1.0f, 0.0f));
	m_PointerPole.SetPostion(glm::vec3(0.0f, 1.445f, 0.3f));

	m_PointerPole.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_PointerBloom.SetPostion(glm::vec3(0.0f, 1.445f, 0.4f));
	m_PointerBloom.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));

	m_Base.SetPostion(glm::vec3(0.0f, 0.0f, 0.5f));
	m_Base.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	
	m_Knob.SetPostion(glm::vec3(0.15f, -0.55f, 0.6f));
	m_Knob.SetScale(glm::vec3(0.4f));

	m_Frame.SetPostion(glm::vec3(0.0f, 0.0f, 0.7f));
	m_Frame.SetScale(glm::vec3(1.0f, 2.0f, 1.0f) * 1.4f);

	
}

void TutorialEnemyUI::Init()
{
	m_Metronome.Clear();
	m_Rotation.Clear();
	m_RotationPoint.SetRotation(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	m_Knob.SetRotation(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	m_Awake = false;
	m_KnobRotation = 0;
	m_RotationCount = 0;
	m_SlotNumber = 0;

}

void TutorialEnemyUI::Update(float ts)
{
	m_Metronome.Update(ts);
	m_Rotation.Update(ts);

	if (m_Rotation)
	{
		if (m_RotationCount != 1)
		{
			m_SlotNumber = (int)(m_Rotation.GetProportion() * 10.0f) + m_RotationCount * 5;
			float r = m_KnobRotation - sin(glm::radians(m_Rotation.GetProportion() * 90.0f)) * 5.0f;
			m_Knob.SetRotation(glm::vec4(0.0f, 0.0f, 1.0f, r));
		}
		else
		{
			m_SlotNumber = 10 + (int)(Engine::Random::Float() * 2.0f);
		}
		
			
		if (m_Rotation.IsTimeOut())
		{
			m_RotationCount++;
			if (m_RotationCount < 3)
			{
				m_Rotation.SetTime(1.0f);
				if (m_RotationCount == 1)
				{
					m_Rotation.SetTime(0.4f);
					m_KnobRotation = -5.0f;
				}
				
			}
			else
			{
				m_KnobRotation = -10.0f;
			}
			
		}
	}
	if (!m_Awake && m_RotationCount == 3)
	{
		m_KnobRotation += ts / 5.0f;
		m_Knob.SetRotation(glm::vec4(0.0f, 0.0f, 1.0f, m_KnobRotation));
	}
	if (m_Awake)
	{
		m_SlotNumber = m_Enemy->GetLife() / 5;
	}
	
	if (m_Metronome)
	{
		float rotation = 0.0f;
		if (m_Wait)
		{
				rotation = m_Forward * sin(glm::radians((float)m_Metronome * 180.0f)) * 0.1f;
		}
		else
		{
			rotation = m_Forward * sin(glm::radians((float)m_Metronome * 180.0f)) * 0.4f;
			
		}

		m_RotationPoint.SetRotation(glm::vec4(0.0f, 0.0f, 1.0f, rotation));
		
	}
}
		

void TutorialEnemyUI::Render(std::shared_ptr<Engine::Camera> camera)
{
	Engine::RendererCommand::SetStencilFunc(ALWAYS, 1, 0xFF);
	Engine::RendererCommand::SetStencilMask(0xFF);
	Engine::Renderer2D::BeginScene(camera);
	Engine::Renderer2D::DrawQuad(m_Background.GetMatrix(), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	Engine::Renderer2D::EndScene();

	
	Engine::RendererCommand::SetStencilFunc(EQUAL, 1, 0xFF);
	Engine::RendererCommand::SetStencilMask(0x00);
	auto texture = m_ObjectManager->GetTextureLibrary()->Get("metronome_ui");
	auto knob = m_ObjectManager->GetTextureLibrary()->Get("metronome");
	if (!m_Awake)
	{
		Engine::Renderer2D::BeginScene(camera, texture);
	
		Engine::Renderer2D::DrawQuad(m_Panel.GetMatrix(), glm::vec4(1.0f), 0.0f);
		Engine::Renderer2D::DrawQuad(m_PointerPole.GetMatrix(), glm::vec4(1.0f), 1.0f);
		Engine::Renderer2D::DrawQuad(m_Base.GetMatrix(), glm::vec4(1.0f), 2.0f);
	
		Engine::Renderer2D::EndScene();

		Engine::Renderer2D::BeginScene(camera, knob);

		Engine::Renderer2D::DrawQuad(m_Knob.GetMatrix(), glm::vec4(1.0f), 1.0f);

		Engine::Renderer2D::EndScene();

		Engine::RendererCommand::SetStencilFunc(ALWAYS, 1, 0xFF);

		Engine::Renderer2D::BeginScene(camera, texture);

		Engine::Renderer2D::DrawQuad(m_Frame.GetMatrix(), glm::vec4(1.0f), 6.0f);

		Engine::Renderer2D::EndScene();
		
		Engine::Renderer2D::BeginScene(camera);

			for (int i = 0; i < m_SlotNumber ; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Slot[i].GetMatrix(), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

			}

		Engine::Renderer2D::EndScene();
		 
		
		
	}
	else
	{
		Engine::Renderer2D::BeginScene(camera, texture);
		Engine::Renderer2D::DrawQuad(m_Panel.GetMatrix(), glm::vec4(glm::vec3(0.0f), 1.0f), 0.0f);
		Engine::Renderer2D::DrawQuad(m_PointerPole.GetMatrix(), glm::vec4(1.0f), 3.0f);
		Engine::Renderer2D::DrawQuad(m_Base.GetMatrix(), glm::vec4(glm::vec3(0.0f), 1.0f), 2.0f);
		Engine::Renderer2D::DrawQuad(m_PanelBloom.GetMatrix(), glm::vec4(glm::vec3(1.5f), 1.0f), 4.0f);
		Engine::Renderer2D::DrawQuad(m_PointerBloom.GetMatrix(), glm::vec4(5.0f, 0.0f, 0.0f, 1.0f), 5.0f);
		Engine::Renderer2D::EndScene();

		Engine::RendererCommand::SetStencilFunc(ALWAYS, 1, 0xFF);

		Engine::Renderer2D::BeginScene(camera, texture);

		Engine::Renderer2D::DrawQuad(m_Frame.GetMatrix(), glm::vec4(1.0f), 6.0f);

		Engine::Renderer2D::EndScene();


		Engine::Renderer2D::BeginScene(camera);

		for (int i = 0; i < m_SlotNumber; i++)
		{
			Engine::Renderer2D::DrawQuad(m_Slot[i].GetMatrix(), glm::vec4(5.0f, 0.0f, 0.0f, 1.0f));

		}

		Engine::Renderer2D::EndScene();


	}
	


}

void TutorialEnemyUI::OnImGuiRender()
{
}

void TutorialEnemyUI::Awake()
{
	m_Awake = true;
}

void TutorialEnemyUI::SetEnemy(std::shared_ptr<TutorialBattleEnemy> enemy)
{
	m_Enemy = enemy;
}

void TutorialEnemyUI::OnBeat()
{
	m_Wait = false;
	m_Forward = -m_Forward;
	m_Metronome.SetTime(60.0f / 100.0f);
}

void TutorialEnemyUI::OnWait()
{
	m_Wait = true;
	m_Forward = -m_Forward;
	m_Metronome.SetTime(60.0f / 100.0f);
}

void TutorialEnemyUI::StartShow()
{
	m_Rotation.SetTime(1.0f);
	m_RotationCount = 0;
}
