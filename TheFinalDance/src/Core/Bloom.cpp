#include "Bloom.h"
#include <imgui.h>
#include <math.h>
Bloom::Bloom()
{
	Engine::ColorAttachmentSpecification fbs[2];
	for (int i = 0; i < 2; i++)
	{
		fbs[i].Width = 1280;
		fbs[i].Height = 720;
		fbs[i].InternalFormat = Engine::RGB16F;
		fbs[i] .Format = Engine::RGB;
		fbs[i] .Filter = Engine::LINEAR;
		fbs[i] .Wrap = Engine::CLAMP_TO_EDGE;

	}
	Engine::RenderBufferSpecification rbs;
	{
		rbs.Width = 1280;
		rbs.Height = 720;
	}
	m_MTRFBO = Engine::MRTFrameBuffer::Create(fbs, 2, &rbs);


	for (int i = 0; i < 3; i++)
	{
		int size = pow(2, i) * 128;
		m_BlurFBSpec[i].Width = size;
		m_BlurFBSpec[i].Height = size;
		m_BlurFBSpec[i].InternalFormat = Engine::RGB16F;
		m_BlurFBSpec[i].Format = Engine::RGB;
		m_BlurFBSpec[i].Filter = Engine::LINEAR;
		m_BlurFBSpec[i].Wrap = Engine::CLAMP_TO_EDGE;

		m_FBOs[i][0] = Engine::FrameBuffer::Create(m_BlurFBSpec[i]);
		m_FBOs[i][1] = Engine::FrameBuffer::Create(m_BlurFBSpec[i]);
	}


	

	m_ShaderBlur = Engine::Shader::Create("assets/shaders/GaussianBlur.glsl");
	m_ShaderBlur->SetInteger("u_Texture0", 0, true);
	m_ShaderBloom = Engine::Shader::Create("assets/shaders/Bloom.glsl");
	m_ShaderBloom->SetInteger("u_Scene", 0, true);
	m_ShaderBloom->SetInteger("u_BloomBlur0", 1);
	m_ShaderBloom->SetInteger("u_BloomBlur1", 2);
	m_ShaderBloom->SetInteger("u_BloomBlur2", 3);
}

void Bloom::Begin() const
{
	m_MTRFBO->Bind();
	Engine::RendererCommand::SetViewport(0, 0, 1280, 720);
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();
}

void Bloom::End()
{
	m_MTRFBO->UnBind();

	m_ShaderBlur->Use();
	m_Horizontal = true;
	bool first= true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_FBOs[j][m_Horizontal]->Bind();
			m_ShaderBlur->SetInteger("u_Horizontal", m_Horizontal);
			if (first)
				m_MTRFBO->BindColorAttachment(0, 1);
			else
				m_FBOs[j][!m_Horizontal]->BindColorAttachment(0);

			Engine::RendererCommand::SetViewport(0, 0, m_BlurFBSpec[j].Width, m_BlurFBSpec[j].Height);
			Engine::RendererPostProcessing::Draw();
		}
		m_Horizontal = !m_Horizontal;
		if (first)
			first = false;
	}
	Engine::RendererCommand::SetViewport(0, 0, 1280, 720);
	m_MTRFBO->UnBind();
}

void Bloom::Render() const
{
	m_ShaderBloom->Use();
	m_MTRFBO->BindColorAttachment(0, 0);
	//m_MTRFBO->BindColorAttachment(1, 1);
	m_FBOs[0][!m_Horizontal]->BindColorAttachment(1);
	m_FBOs[1][!m_Horizontal]->BindColorAttachment(2);
	m_FBOs[2][!m_Horizontal]->BindColorAttachment(3);
	m_ShaderBloom->SetFloat("u_Exposure", m_Exposure);
	Engine::RendererPostProcessing::Draw();
}

void Bloom::OnImGuiRender()
{
	ImGui::Begin("Bloom");
	ImGui::DragFloat("Exposure", &m_Exposure, 0.001f, 0.0f, 5.0f);
	ImGui::Image((void*)m_MTRFBO->GetColorAttachment(0), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
	ImGui::Image((void*)m_MTRFBO->GetColorAttachment(1), ImVec2{ 320,180 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
	ImGui::End();
}


