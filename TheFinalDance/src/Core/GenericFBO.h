#pragma once
#include "Core/ObjectManager.h"
#include "Engine.h"
#include <imgui.h>
class GenericFBO : public PostObject
{
public:
	//�����ʼ������
	virtual void Init() override
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
	//���º���
	//����ʱ��ĸ���
	virtual void Update(float ts) override
	{
	}

	//������Ⱦ����
	virtual void Render(std::shared_ptr<Engine::Camera> camera) override
	{
		m_ObjectManager->GetShaderLibrary()->Get("FBO")->Use();
		m_FBO->BindColorAttachment();
		Engine::RendererPostProcessing::Draw();
	}
	//����UI��Ⱦ
	virtual void OnImGuiRender() override
	{
		ImGui::Text("GenericFBO:");
		ImGui::Image((void*)m_FBO->GetColorAttachment(), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
	}
	virtual void Bind() override
	{
		m_FBO->Bind();
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
		Engine::RendererCommand::Clear();
		Engine::RendererCommand::EnableDepthTest();
	}
	virtual void UnBind() override
	{
		m_FBO->UnBind();
	}

private:
	std::shared_ptr<Engine::FrameBuffer> m_FBO;
};

