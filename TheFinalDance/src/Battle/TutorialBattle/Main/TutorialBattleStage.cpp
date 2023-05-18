#include "TutorialBattleStage.h"
#include "Core/ObjectManager.h"
#include <imgui.h>
TutorialBattleStage::TutorialBattleStage()
{
	m_Stage.resize(7 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{

			m_Stage[j * 7 + i].Index = j * 7 + i;
			m_Stage[j * 7 + i].Postion.SetFather(&m_MainTransform);
			m_Stage[j * 7 + i].Postion.SetScale(glm::vec3(0.95f));


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
void TutorialBattleStage::Init()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{

			m_Stage[j * 7 + i].Postion.SetPostion(glm::vec3(i - 3, j - 3, -1.0));
			m_Stage[j * 7 + i].Step = 0;
			m_Stage[j * 7 + i].Occupy = false;
			m_Stage[j * 7 + i].Danger = false;
			m_Stage[j * 7 + i].Awake = i == 3 && (j == 2 || j == 3);
				
		}
	}
}

void TutorialBattleStage::Update(float ts)
{
	m_Start.Update(ts);
	if (m_Start)
	{
		BlockBack();
		if (m_Start.IsTimeOut())
		{
			m_Number++;
			if (m_Number <= 4 && m_Number >1)
			{
				
				SoundEngine::Play2D(m_ObjectManager->GetSoundSourceLibrary()->Get("brick"));
				if (m_Number == 4)
				{
					m_Start.Clear();
				}
			}
			
			

			
		}
		
	}
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
				if (m_Stage[i].Danger)
				{
					glm::vec3 color = { Engine::Random::Float() * 5.0f , Engine::Random::Float() * 5.0f, Engine::Random::Float() * 5.0f };
					Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(color * m_Brightness, 1.0f), -3.0f);
				}
				else
				{
					Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(m_Color * m_Brightness,1.0f), -1.0f);
				}
				
				if (m_Stage[i].Step <= 9)
				{
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number1.GetMatrix(), glm::vec4(m_Color * m_Brightness, 1.0f), m_Stage[i].Step);
				}
				else
				{
					int x = m_Stage[i].Step / 10;
					int y = m_Stage[i].Step % 10;
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number1.GetMatrix(), glm::vec4(m_Color * m_Brightness, 1.0f), x);
					Engine::Renderer2D::DrawQuad(m_Stage[i].Number2.GetMatrix(), glm::vec4(m_Color * m_Brightness, 1.0f), y);
				}

			}
			else
			{ 
				if (m_Stage[i].Danger)
				{
					glm::vec3 color = { Engine::Random::Float() * 5.0f , Engine::Random::Float() * 5.0f, Engine::Random::Float() * 5.0f };
					Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(color * m_Brightness, 1.0f), -3.0f);
				}
				else
				{
					Engine::Renderer2D::DrawQuad(m_Stage[i].Postion.GetMatrix(), glm::vec4(m_Color * m_Brightness, 1.0f), -2.0f);
				}
				
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

void TutorialBattleStage::StartShow()
{
	m_Start.SetTime(0.5f);
	m_Start.SetLoop(true);
	m_Number = 0;
}

void TutorialBattleStage::Start()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{

			m_Stage[j * 7 + i].Postion.SetPostion(glm::vec3(i - 3, j - 3, -1.0));

			m_Stage[j * 7 + i].Awake = true;
		}
	}
}

void TutorialBattleStage::BlockBack()
{
	
	if (m_Number > 0)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 3 - m_Number || i == 3 + m_Number || j == 3 - m_Number || j == 3 + m_Number)
					&& i >= 3 - m_Number && i <= 3 + m_Number && j >= 3 - m_Number && j <= 3 + m_Number
					&& !(i == 3 && j == 2))
				{

					glm::vec3 position = glm::vec3(i - 3, j - 3, -1.0) * 3.0f + (glm::vec3(i - 3, j - 3, -1.0) - glm::vec3(i - 3, j - 3, -1.0) * 3.0f) * m_Start.GetProportion();
					m_Stage[j * 7 + i].Awake = true;
					m_Stage[j * 7 + i].Postion.SetPostion(position);
				}
			}
		}
	}
	
}
