#include "TutorialBattleStage.h"
#include "Core/ObjectManager.h"
void TutorialBattleStage::Init()
{
	m_Stage.resize(7 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{

			m_Stage[j * 7 + i].Transform.SetFather(&m_MainTransform);
			m_Stage[j * 7 + i].Transform.SetPostion(glm::vec3(i - 3, j - 3, -1.0));
			m_Stage[j * 7 + i].Transform.SetScale(glm::vec3(0.95f));
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
				m_Stage[j * 7 + i].Link[0] = &m_Stage[j * 7 + i - 7];
			}
			if (j < 6)
			{
				m_Stage[j * 7 + i].Link[1] = &m_Stage[j * 7 + i + 7];
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
	float alpha = 1.0f;

	Engine::Renderer2D::BeginScene(camera, texture, shader);
	for (int i = 0; i < m_Stage.size(); i++)
	{
		if (m_Stage[i].Awake)
		{

			Engine::Renderer2D::DrawQuad(m_Stage[i].Transform.GetMatrix(), glm::vec4(1.0f, 1.0f, 1.0f, alpha), 0.0f);

		}

	}
	Engine::Renderer2D::EndScene();
}

void TutorialBattleStage::OnImGuiRender()
{
}
