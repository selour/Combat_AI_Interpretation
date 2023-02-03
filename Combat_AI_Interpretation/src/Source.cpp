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
		//¶¥µãÔØÈë

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		m_VAO = Engine::VertexArray::Create();
		m_VBO = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
		m_EBO = Engine::ElementBuffer::Create(indices, sizeof(indices) / sizeof(unsigned));


		{
			Engine::BufferLayout layout = {
				{ Engine::ShaderDataType::Float3, "a_Position" },
				{ Engine::ShaderDataType::Float2, "a_TexCoord" }
			};
			m_VBO->SetLayout(layout);
		}
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetElementBuffer(m_EBO);

		

		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->SetInteger("u_Texture", 0);
		m_Texture = Engine::Texture2D::Create("assets/textures/eye.png");
		//m_Camera.SetRotation(45.0f);
	
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


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);


		//glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();

		


		Engine::Renderer::BeginScene(m_CameraController.GetCamera());

		std::dynamic_pointer_cast<Engine::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->SetVector3f("u_Color", m_Color);
		m_Texture->Bind(0);

		Engine::Renderer::Submit(m_VAO, m_ShaderLibrary.Get("Texture"), transform);
		Engine::Renderer::EndScene();

	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}
	void OnEvent(Engine::Event& event) override
	{
		m_CameraController.OnEvent(event);
		//ENGINE_TRACE("{0}", event.ToString());
	}
private:
	Engine::ShaderLibrary m_ShaderLibrary;
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::VertexBuffer> m_VBO;
	std::shared_ptr<Engine::ElementBuffer> m_EBO;
	std::shared_ptr<Engine::Texture2D> m_Texture;

	Engine::OrthographicCameraController m_CameraController;	
	float m_MoveSpeed = 0.5f;
	glm::vec3 m_Color = glm::vec3(1.0f);
	glm::vec3 m_Position = glm::vec3(0.0f);
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