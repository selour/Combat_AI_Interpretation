#include "BrightFBO.h"
#include <imgui.h>
BrightFBO::BrightFBO()
{
	Engine::ColorAttachmentSpecification cas;

	cas.Width = 1280;
	cas.Height = 720;
	cas.InternalFormat = Engine::RGBA16F;
	cas.Format = Engine::RGBA;
	cas.Filter = Engine::LINEAR;
	cas.Wrap = Engine::CLAMP_TO_EDGE;

	Engine::RenderBufferSpecification rbs;
	rbs.Width = 1280;
	rbs.Height = 720;


	m_FBO = Engine::FrameBuffer::Create(cas, rbs);
}
void BrightFBO::Init()
{
}

void BrightFBO::Update(float ts)
{
	
}

void BrightFBO::Render(std::shared_ptr<Engine::Camera> camera)
{
	m_ObjectManager->GetShaderLibrary()->Get("Bright")->Use();
	m_FBO->BindColorAttachment();
	Engine::RendererPostProcessing::Draw();
}

void BrightFBO::OnImGuiRender()
{
	ImGui::Text("BrightFBO:");
	ImGui::Image((void*)m_FBO->GetColorAttachment(), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
}

void BrightFBO::Bind()
{
	m_FBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	if (m_DepthTest)
	{
		Engine::RendererCommand::EnableDepthTest();
	}
	else
	{
		Engine::RendererCommand::DisableDepthTest();
	}
}

void BrightFBO::UnBind()
{
	Engine::RendererCommand::ClearDepthBuffer();
	Engine::RendererCommand::ClearStencilBuffer();
	m_FBO->UnBind();
}

void BrightFBO::SetDepthTest(bool enable)
{
	m_DepthTest = enable;
}
