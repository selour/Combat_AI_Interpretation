#include "Bloom.h"

Bloom::Bloom()
{
	Engine::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_MTRFBO = Engine::MRTFrameBuffer::Create(fbSpec, 2);
	m_FBOs[0] = Engine::FrameBuffer::Create(fbSpec);
	m_FBOs[1] = Engine::FrameBuffer::Create(fbSpec);

	m_ShaderBlur = Engine::Shader::Create("assets/shaders/GaussianBlur.glsl");
	m_ShaderBlur->SetInteger("u_Texture0", 0, true);
	m_ShaderBloom = Engine::Shader::Create("assets/shaders/Bloom.glsl");
	m_ShaderBloom->SetInteger("u_Scene", 0, true);
	m_ShaderBloom->SetInteger("u_BloomBlur", 1, true);
}

void Bloom::Begin() const
{
	m_MTRFBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Engine::RendererCommand::Clear();
}

void Bloom::End()
{
	m_MTRFBO->UnBind();

	m_ShaderBlur->Use();
	m_Horizontal = true;
	bool first= true;
	for (int i = 0; i < m_Amount; i++)
	{
		m_FBOs[m_Horizontal]->Bind();
		m_ShaderBlur->SetInteger("u_Horizontal", m_Horizontal);
		if (first)
			m_MTRFBO->BindColorAttachment(0, 1);
		else
			m_FBOs[!m_Horizontal]->BindColorAttachment(0);
		Engine::RendererPostProcessing::Draw();
		m_Horizontal = !m_Horizontal;
		if (first)
			first = false;
	}
	m_MTRFBO->UnBind();
}

void Bloom::Render() const
{
	m_ShaderBloom->Use();
	m_MTRFBO->BindColorAttachment(0, 0);
	//m_MTRFBO->BindColorAttachment(1, 1);
	m_FBOs[!m_Horizontal]->BindColorAttachment(1);
	m_ShaderBloom->SetFloat("u_Exposure", m_Exposure);
	Engine::RendererPostProcessing::Draw();
}


