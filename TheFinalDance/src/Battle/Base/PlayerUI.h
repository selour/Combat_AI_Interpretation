#pragma once
#include "BattleUI.h"
#include "BattlePlayer.h"
#include "Core/GameTimer.h"
class PlayerUI : public BattleUI
{
public:
	PlayerUI()
	{
		m_Main.SetPostion(glm::vec3(-1.28f, 0.0f, 0.0f));
		m_Main.SetScale(glm::vec3(0.9f));
		m_Background.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));

		m_LifeSlot.SetFather(&m_Frame);
		m_LifeSlot.SetPostion(glm::vec3(0.35f, -0.88f, 0.1f));
		//m_LifeSlot.SetScale(glm::vec3(0.15f, 1.2f, 1.0f));
		for (int i = 0; i < 8; i++)
		{

			m_Slot[i].SetFather(&m_LifeSlot);
			m_Slot[i].SetPostion(glm::vec3(0.0f, i * 0.11f, 0.0f));
			m_Slot[i].SetScale(glm::vec3(0.10f));

		}

		m_ComboCount.SetFather(&m_Frame);
		m_ComboCount.SetPostion(glm::vec3(0.55f, 0.70f, 0.1f));
		for (int i = 0; i < 3; i++)
		{
			m_Number[i].SetFather(&m_ComboCount);
			m_Number[i].SetPostion(glm::vec3(-0.2f * i, 0.0f, 0.1f));
			m_Number[i].SetScale(glm::vec3(0.2f));
		}
	}
	void OnUpdate(float ts)
	{
		m_Combo.Update(ts);
		int count = m_Player->GetComboCount();
		if (count != m_LastCombo && count != 0)
		{
			m_Combo.SetTime(0.15f);
		}
		m_LastCombo = count;
		m_Digit = 0;
		while (count != 0 && m_Digit < 3)
		{
			m_ComboNumber[m_Digit] = count % 10;
			count /= 10;
			m_Digit++;
		}

		if (m_Combo)
		{
			m_ComboCount.SetScale(glm::vec3(1.0f + 0.15f * sin(glm::radians(m_Combo.GetProportion() * 180.0f))));
		}
	}
	void OnRender(std::shared_ptr<Engine::Camera> camera)
	{

		Engine::Renderer2D::BeginScene(camera);
		Engine::Renderer2D::DrawQuad(m_Background.GetMatrix(), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

		//Engine::Renderer2D::DrawQuad(m_LifeSlot.GetMatrix(), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Engine::Renderer2D::EndScene();



		auto texture = m_ObjectManager->GetTextureLibrary()->Get("player");
		Engine::Renderer2D::BeginScene(camera, texture);

		for (int i = 0; i < m_Player->GetLife(); i++)
		{
			Engine::Renderer2D::DrawQuad(m_Slot[i].GetMatrix(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 3.0f);
		}

		Engine::Renderer2D::EndScene();


		auto number = m_ObjectManager->GetTextureLibrary()->Get("number");





		Engine::Renderer2D::BeginScene(camera, number);

		for (int i = 0; i < m_Digit; i++)
		{
			Engine::Renderer2D::DrawQuad(m_Number[i].GetMatrix(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), m_ComboNumber[i]);
		}

		Engine::Renderer2D::EndScene();
	}

	void SetPlayer(std::shared_ptr<BattlePlayer> player)
	{
		m_Player = player;
	}
protected:

	std::shared_ptr<BattlePlayer> m_Player;

	Transform m_LifeSlot;
	Transform m_Slot[8];

	Transform m_ComboCount;
	Transform m_Number[3];
	int m_Digit = 0;
	int m_ComboNumber[3] = { 0,0,0 };
	int m_LastCombo = 0;
	GameTimer m_Combo;
};
	

