#include "BackgroundFBO.h"
#include <imgui.h>
void BackgroundFBO::Init()
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

void BackgroundFBO::Update(float ts)
{
}

void BackgroundFBO::Render(std::shared_ptr<Engine::Camera> camera)
{
	m_ObjectManager->GetShaderLibrary()->Get("Bright")->Use();
	m_FBO->BindColorAttachment();
	Engine::RendererPostProcessing::Draw();
}

void BackgroundFBO::OnImGuiRender()
{
	ImGui::Text("BackgroundFBO:");
	ImGui::Image((void*)m_FBO->GetColorAttachment(), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
}

void BackgroundFBO::Bind()
{
	m_FBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	Engine::RendererCommand::EnableDepthTest();
}

void BackgroundFBO::UnBind()
{
	m_FBO->UnBind();
}
