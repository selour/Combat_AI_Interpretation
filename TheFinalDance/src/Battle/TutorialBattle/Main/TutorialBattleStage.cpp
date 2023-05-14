#include "TutorialBattleStage.h"
#include "Core/ObjectManager.h"
#include <imgui.h>
void TutorialBattleStage::Init()
{
	m_Stage.resize(7 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{

			m_Stage[j * 7 + i].Postion.SetFather(&m_MainTransform);
			m_Stage[j * 7 + i].Postion.SetPostion(glm::vec3(i - 3, j - 3, -1.0));
			m_Stage[j * 7 + i].Postion.SetScale(glm::vec3(1.0f));
			m_Stage[j * 7 + i].Init();
			m_Stage[j * 7 + i].Awake = true;
			if (i > 0)
			{
				m_Stage[j * 7 + i].Link[2] = &m_Stage[j * 7 + i - 1];
			}
			if (i < 6)
			{
				m_Stage[j * 7 + i].Link[3] = &m_Stage[j * 7 + i + 1];
			}
			if (j > 0)
			{
				m_Stage[j * 7 + i].Link[1] = &m_Stage[j * 7 + i - 7];
			}
			if (j < 6)
			{
				m_Stage[j * 7 + i].Link[0] = &m_Stage[j * 7 + i + 7];
			}
		}
	}
}

void TutorialBattleStage::Update(float ts)
{
}


void TutorialBattleStage::Render(std::shared_ptr<Engine::Camera> camera)
{
	auto shader = m_ObjectManager->GetShaderLibrary()->Get("Block");
	auto texture = m_ObjectManager->GetTextureLibrary()->Get("number");

	Engine::Renderer2D::BeginScene(camera, texture, shader);
	for (int i = 0; i < m_Stage.size(); i++)
	{
		if (m_Stage[i].Awake)
		{
			if (m_Stage[i].Step != 0)
			{
				Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(m_Color * m_Brightness,1.0f), -1.0f);
				if (m_Stage[i].Step <= 9)
				{
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number1.GetMatrix(), glm::vec4(1.0f), m_Stage[i].Step);
				}
				else
				{
					int x = m_Stage[i].Step / 10;
					int y = m_Stage[i].Step % 10;
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number1.GetMatrix(), glm::vec4(1.0f), x);
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number2.GetMatrix(), glm::vec4(1.0f), y);
				}

			}
			else
			{ 
				Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(m_Color * m_Brightness, 1.0f), -2.0f);
			}
		}

	}
	Engine::Renderer2D::EndScene();
}

void TutorialBattleStage::OnImGuiRender()
{
	ImGui::Text("Stage:");
	ImGui::DragFloat("Stage Brightness", &m_Brightness, 0.001f, 0.0f, 5.0f);
	ImGui::DragFloat3("Stage Color", &m_Color.r, 0.001f, 0.0f, 1.0f);
}
