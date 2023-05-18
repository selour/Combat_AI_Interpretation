#include "TutorialDangerControl.h"

TutorialDangerControl::TutorialDangerControl()
{
}

void TutorialDangerControl::Init()
{
}

void TutorialDangerControl::Update(float ts)
{
	m_Timer.Update(ts);
	OnUpdate(ts);
	if (m_Timer)
	{
		if (m_Timer.IsTimeOut())
		{
			if (m_Count == 7)
			{
				m_Timer.Clear();
			}
			else
			{

				switch (m_RandomMode)
				{
				case 0:
					for (int i = 0; i < 7; i++)
					{
						Submit((6 - m_Count) * 7 + i, 0.6f / 8.0f);

					}
					break;
				case 1:
					for (int i = 0; i < 7; i++)
					{
						Submit(m_Count * 7 + i, 0.6f / 8.0f);

					}
					break;
				case 2:
					for (int i = 0; i < 7; i++)
					{
						Submit(i * 7 + m_Count, 0.6f / 8.0f);


					}
					break;
				case 3:
					for (int i = 0; i < 7; i++)
					{
						Submit(i * 7 + (6 - m_Count), 0.6f / 8.0f);

					}
					break;
				}

				m_Count++;
			}
			
		}
	}
	
}

void TutorialDangerControl::Render(std::shared_ptr<Engine::Camera> camera)
{
	if (m_Timer && m_Count != 7)
	{
		auto texture = m_ObjectManager->GetTextureLibrary()->Get("danger");
		Engine::Renderer2D::BeginScene(camera,texture);
		switch (m_RandomMode)
		{
		case 0:
			for (int i = 0; i < 7; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Stage->GetBlock((6 - m_Count) * 7 + i)->Postion.GetMatrix(), glm::vec4(2.0f, 0.0f, 0.0f, 0.9f));

			}
			break;
		case 1:
			for (int i = 0; i < 7; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Stage->GetBlock(m_Count * 7 + i)->Postion.GetMatrix(), glm::vec4(2.0f, 0.0f, 0.0f, 0.9f));

			}
			break;
		case 2:
			for (int i = 0; i < 7; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Stage->GetBlock(i * 7 + m_Count)->Postion.GetMatrix(), glm::vec4(2.0f, 0.0f, 0.0f, 0.9f));

			}
			break;
		case 3:
			for (int i = 0; i < 7; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Stage->GetBlock(i * 7 + (6 - m_Count))->Postion.GetMatrix(), glm::vec4(2.0f, 0.0f, 0.0f, 0.9f));

			}
			break;
		}
		Engine::Renderer2D::EndScene();
	}
		

}

void TutorialDangerControl::OnImGuiRender()
{
}

bool TutorialDangerControl::IsActive()
{
	return m_Timer;
}

void TutorialDangerControl::Active()
{
	m_Count = 0;
	m_RandomMode = Engine::Random::Float() * 4;
	m_Timer.SetTime(60.0f / (float)m_BPM);
	m_Timer.SetLoop(true);
}

void TutorialDangerControl::End()
{
	m_Timer.Clear();
	Clear();
}
