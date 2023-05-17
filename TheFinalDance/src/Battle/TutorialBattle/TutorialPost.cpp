#include "TutorialPost.h"

TutorialPost::TutorialPost()
{
	Engine::ColorAttachmentSpecification cas;

	cas.Width = 1280;
	cas.Height = 720;
	cas.InternalFormat = Engine::RGB8;
	cas.Format = Engine::RGB;
	cas.Filter = Engine::LINEAR;
	cas.Wrap = Engine::CLAMP_TO_EDGE;

	m_FBO = Engine::FrameBuffer::Create(cas);
}

void TutorialPost::Init()
{
	m_Time = 0;
	m_Awake = false;
}

void TutorialPost::Update(float ts)
{
	m_Time += ts;
	m_Noise.Update(ts);
	m_Rhythm.Update(ts);
}

void TutorialPost::Render(std::shared_ptr<Engine::Camera> camera)
{
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	auto shader = m_ObjectManager->GetShaderLibrary()->Get("Post");
	shader->SetFloat("u_Time", m_Time, true);
	shader->SetVector2f("u_Resolution", glm::vec2(1280.0f, 720.0f));
	shader->SetFloat("u_Rhythm", sin(glm::radians(m_Rhythm.GetProportion() * 180.0f)));

	if (m_Noise)
	{
		shader->SetInteger("u_State", 1);
	}
	else
	{
		if (m_Awake)
		{
			shader->SetInteger("u_State", 2);
		}
		else
		{
			shader->SetInteger("u_State", 0);
		}

	}
	Engine::RendererPostProcessing::Draw(m_FBO, shader);
}

void TutorialPost::OnImGuiRender()
{
}

void TutorialPost::Bind()
{
	m_FBO->Bind();
	Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	Engine::RendererCommand::Clear();
	Engine::RendererCommand::DisableDepthTest();
}

void TutorialPost::UnBind()
{
	m_FBO->UnBind();
}
