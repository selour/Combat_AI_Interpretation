#include "Heart.h"
#include "Core/ObjectManager.h"
#include <imgui.h>
Heart::Heart()
{
	
}

void Heart::Init()
{
	const glm::vec2 pos[5] = {
		{0.045f, -0.571f},
		{ -0.711f, 0.044f },
		{ 0.4f, 0.22f },
		{ 0.177f, 0.7f },
		{ -0.356f, 0.747f } };
	for (int i = 0; i < 5; i++)
	{
		m_Part[i].SetFather(&m_Main);
		m_Part[i].SetPostion({ pos[i].x,pos[i].y,0.0 });
		m_Part[i].SetScale(glm::vec3(1.3f));
	}
}

void Heart::Update(float ts)
{
	if (m_Awake)
	{
		m_Beat.Update(ts);
		if(m_Beat)
		{
			for (int i = 0; i < 5; i++)
			{
				m_Part[i].SetScale(glm::vec3(1.3f + 0.15f * sin(glm::radians(m_Beat.GetProportion() * 180.0f)))); 
			}
		}
	}
	
}

void Heart::Render(std::shared_ptr<Engine::Camera> camera)
{
	if (m_Awake)
	{
		auto texture = m_ObjectManager->GetResourceManager()->GetTextureLibrary()->Get("heart");
		Engine::Renderer2D::BeginScene(camera, texture);
		{
			for (int i = 0; i < 5; i++)
			{
				Engine::Renderer2D::DrawQuad(m_Part[i].GetMatrix(), glm::vec4(glm::vec3(1.0f) * m_Brightness,1.0f), float(i));
			}
		}
		Engine::Renderer2D::EndScene();
	}
}



void Heart::OnImGuiRender()
{
	ImGui::Text("Heart:");
	ImGui::DragFloat("Heart Brightness", &m_Brightness, 0.001f, 0.0f, 5.0f);
}

void Heart::OnBeat()
{
	if (m_Awake)
	{
		m_Beat.SetTime(0.15f);
	}
	
}
void Heart::Awake()
{
	m_Awake = true;

}
