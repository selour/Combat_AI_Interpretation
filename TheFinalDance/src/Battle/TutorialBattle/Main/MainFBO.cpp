#include "MainFBO.h"
#include <imgui.h>
void MainFBO::Init()
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

void MainFBO::Update(float ts)
{
	
}

void MainFBO::Render(std::shared_ptr<Engine::Camera> camera)
{
	m_ObjectManager->GetShaderLibrary()->Get("Bright")->Use();
	m_FBO->BindColorAttachment();
	Engine::RendererPostProcessing::Draw();
}

void MainFBO::OnImGuiRender()
{
	ImGui::Text("BackgroundFBO:");
	ImGui::Image((void*)m_FBO->GetColorAttachment(), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
}

void MainFBO::Bind()
{
	m_FBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	Engine::RendererCommand::DisableDepthTest();
}

void MainFBO::UnBind()
{
	m_FBO->UnBind();
}
