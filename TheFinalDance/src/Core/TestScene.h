#pragma once
#include "Core/Scene.h"
class TestScene : public Scene
{
public:
	TestScene()
		:Scene("Test")
	{}
	virtual void OnAttach() override
	{
		m_Shader = Engine::Shader::Create("assets/shaders/purity.glsl");
	}

	virtual void OnDetach() override
	{}
	virtual void OnUpdate(Engine::TimeStep ts) override
	{
		m_Time += ts;
	}

	virtual void OnRender() override
	{
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
		Engine::RendererCommand::Clear();
		Engine::RendererCommand::DisableDepthTest();
		m_Shader->Use();
		m_Shader->SetFloat("v_Time", m_Time);
		Engine::RendererPostProcessing::Draw();
		m_Shader->UnUse();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("TestScene");
		ImGui::Text("Time:%.2f s", m_Time);
		ImGui::End();
	}

private:
	float m_Time = 0;
	std::shared_ptr<Engine::Shader> m_Shader;
};

