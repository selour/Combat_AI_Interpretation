#include "Engine.h"
#include "imgui.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

class TestLayer : public Engine::Layer
{
public:
	TestLayer()
		:Layer("Test"), m_CameraController(1280.0f / 720.0f, true)
	{
		
		
	
	}
	void OnAttach()
	{
		m_Texture = Engine::Texture2D::Create("assets/textures/eye.png");
	}

	void OnUpdate(Engine::TimeStep ts) override
	{
		m_CameraController.OnUpdate(ts);

		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_LEFT))
			m_Position.x -= m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_RIGHT))
			m_Position.x += m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_UP))
			m_Position.y += m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_DOWN))
			m_Position.y -= m_MoveSpeed * ts;




		
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();

		


		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		
		Engine::Renderer2D::DrawRotatedQuad(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec2(10.0f), glm::radians(45.0f), glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f));
		Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(1.0f), m_Texture, m_Color);
		

		Engine::Renderer2D::EndScene();

	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}
	void OnEvent(Engine::Event& event) override
	{
		m_CameraController.OnEvent(event);
		//ENGINE_TRACE("{0}", event.ToString());
	}
private:
	
	std::shared_ptr<Engine::Texture2D> m_Texture;

	Engine::OrthographicCameraController m_CameraController;	
	float m_MoveSpeed = 0.5f;
	glm::vec4 m_Color = glm::vec4(1.0f);
	glm::vec2 m_Position = glm::vec2(0.0f);
};

class Game : public Engine::Application
{
public:
	Game()
	{
		AppPushLayer(new TestLayer());
	}

	~Game()
	{
	}

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}