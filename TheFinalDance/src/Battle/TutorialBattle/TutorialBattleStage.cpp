#include "TutorialBattleStage.h"
#include "Core/ObjectManager.h"
void TutorialBattleStage::Init()
{
}

void TutorialBattleStage::Update(float ts)
{
}

void TutorialBattleStage::BufferRender()
{
}

void TutorialBattleStage::Render()
{
	auto shader = m_ObjectManager->GetShaderLibrary()->Get("Block");
	auto texture = m_ObjectManager->GetTextureLibrary()->Get("number");
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

void TutorialBattleStage::OnImGuiRender()
{
}
