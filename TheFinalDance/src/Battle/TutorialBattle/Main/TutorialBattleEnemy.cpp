#include "TutorialBattleEnemy.h"
#include <imgui.h>
void TutorialBattleEnemy::Init()
{
	m_Life = 100;
	m_LifeLock = true;
}

void TutorialBattleEnemy::Update(float ts)
{
	OnUpdate(ts);
}

void TutorialBattleEnemy::Render(std::shared_ptr<Engine::Camera> camera)
{
	if (m_Active)
	{
		auto beatTipShader = m_ObjectManager->GetShaderLibrary()->Get("BeatTip");
		auto EnemyShader = m_ObjectManager->GetShaderLibrary()->Get("Enemy");
		auto texture = m_ObjectManager->GetTextureLibrary()->Get("metronome");

		

		Engine::Renderer2D::BeginScene(camera, nullptr, beatTipShader);
		
		bool onCheck = false;
		for (int i = 0; i < m_BeatTips.size(); i++)
		{
			auto beatTip = m_BeatTips[i];
			if (beatTip.IsActive)
			{
				onCheck = onCheck || beatTip.CheckFlag;
				if (!beatTip.CheckFlag)
				{
					Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(m_BeatTipSize), 0, m_BeatTipColor, beatTip.BeatCheck.GetProportion(0));

				}
			}

		}
		if (onCheck)
		{
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(m_BeatTipSize / 3.0f), 0, m_BeatCheckColor, -1.0f);
		}
		else
		{
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(m_BeatTipSize / 3.0f), 0, m_BeatTipColor, -1.0f);
		}

		Engine::Renderer2D::EndScene();

		Engine::Renderer2D::BeginScene(camera, texture, EnemyShader);
		if (m_HitFlag.GetFlag())
		{
			EnemyShader->SetFloat("u_Hit", m_HitFlag.GetProportion());
		}
		else
		{
			EnemyShader->SetFloat("u_Hit", -1.0f);
		}
		
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(m_Size), 0, glm::vec4(1.0f), 0.0f);
		Engine::Renderer2D::EndScene();
	}
	
}

void TutorialBattleEnemy::OnImGuiRender()
{
	ImGui::Text("EnemyLife: %d", m_Life);
	ImGui::Text("BeatTipPool:");
	for (int i = 0; i < m_BeatTips.size(); i++)
	{
		auto beatTip = m_BeatTips[i];
		ImGui::Text("%d Active:%d,CheckFlag:%d, Tip:%.2f, Check:%.2f",
			i, beatTip.IsActive, beatTip.CheckFlag, beatTip.BeatCheck.GetProportion(0), beatTip.BeatCheck.GetProportion(1));;
		ImGui::Text("Time:%.2f, CurrentIndex:%d", beatTip.BeatCheck.GetTime(), beatTip.BeatCheck.GetCurrentIndex());
		if (!beatTip.BeatCheck.GetTimeLine().empty())
		{
			for (int j = 0; j < beatTip.BeatCheck.GetTimeLine().size(); j++)
			{
				ImGui::Text("TimePoint:%.2f, Flag:%d", beatTip.BeatCheck.GetTimeLine()[j].Time, beatTip.BeatCheck.GetTimeLine()[j].Flag);
			}
		}
			
	
	
	}
}

void TutorialBattleEnemy::HitBind(int step)
{
	if (!m_LifeLock)
	{
		m_Life -= step + 3;
		if (m_Life < 0)
			m_Life = 0;
	}
		
}

void TutorialBattleEnemy::Unlock()
{
	m_LifeLock = false;
}

void TutorialBattleEnemy::RandomBlock()
{
	int i = 3 * 7 + 3;
	while (i == 3 * 7 + 3 || i == m_Current)
	{
		i = int(Engine::Random::Float() * 49);
	}

	SetBlock(i);
}

int TutorialBattleEnemy::GetLife()
{
	return m_Life;
}

