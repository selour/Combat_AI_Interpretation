#include "HeartFBO.h"
#include <imgui.h>
HeartFBO::HeartFBO()
{
	Engine::ColorAttachmentSpecification cas;

	cas.Width = 1280;
	cas.Height = 720;
	cas.InternalFormat = Engine::RGBA16F;
	cas.Format = Engine::RGBA;
	cas.Filter = Engine::LINEAR;
	cas.Wrap = Engine::CLAMP_TO_EDGE;

	m_FBO = Engine::FrameBuffer::Create(cas);
}
void HeartFBO::Init()
{
	
}

void HeartFBO::Update(float ts)
{
}

void HeartFBO::Render(std::shared_ptr<Engine::Camera> camera)
{
	if (m_Heart->m_Awake)
	{
		float color = (0.6f + 0.1f * sin(glm::radians(m_Heart->m_Beat.GetProportion() * 180.0f))) * m_Brightness;
		auto shader = m_ObjectManager->GetShaderLibrary()->Get("Heart");
		shader->SetFloat("v_Color", color, true);
		shader->SetFloat("v_Shadow", m_Heart->m_Beat.GetProportion());
		Engine::RendererPostProcessing::Draw(m_FBO, shader);
	}
	
}

void HeartFBO::OnImGuiRender()
{
	ImGui::Text("HeartFBO:");
	ImGui::DragFloat("HeartBrightness", &m_Brightness, 0.001f, 0.0f, 5.0f);
	ImGui::Image((void*)m_FBO->GetColorAttachment(), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
}

void HeartFBO::Bind()
{
	m_FBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	Engine::RendererCommand::EnableDepthTest();
}

void HeartFBO::UnBind()
{
	m_FBO->UnBind();
}
