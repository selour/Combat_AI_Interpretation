#include "Engine.h"
#include "imgui.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static float timer = 0.0f;
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
		m_SpriteSheet = Engine::Texture2DArray::Create("assets/textures/eye.png", 1, 1);
		/*
		//…Ë÷√¡£◊”
		m_Particle.ColorBegin = m_Color;
		m_Particle.ColorEnd = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
		
		m_Particle.SizeBegin = 0.1f;
		m_Particle.SizeEnd = 0.0f;

		m_Particle.LifeTime = 1.0f;
		m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Particle.VelocityVariation = glm::vec3(1.0f, 1.0f, 0.0f);
		m_Particle.Position = glm::vec3(0.0f, 0.0f, 0.1f);
		*/
	}

	void OnUpdate(Engine::TimeStep ts) override
	{
		m_FPS = 1.0f / ts;
		m_CameraController.OnUpdate(ts);

		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_LEFT))
			m_Position.x -= m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_RIGHT))
			m_Position.x += m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_UP))
			m_Position.y += m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_DOWN))
			m_Position.y -= m_MoveSpeed * ts;



		timer += ts * 2;
		
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();

		

		Engine::Renderer2D::ResetStats();
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		glm::vec4 quadColor = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
		for (float y = -5.0f; y < 5.0f; y += 0.25f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.25f)
			{
				Engine::Renderer2D::DrawQuad(glm::vec3(x, y, -0.1f), glm::vec2(0.23f), 0, quadColor);
			}
		}
		Engine::Renderer2D::EndScene();

		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera(), m_SpriteSheet);

		Engine::Renderer2D::DrawQuad(glm::vec3(1.4f, -0.7f, 0.0f), glm::vec2(0.3f), 0, glm::vec4(1.0f));

		Engine::Renderer2D::EndScene();
		//Engine::Renderer2D::DrawQuad(glm::vec3(1.4f, -0.7f, 0.0f), glm::vec2(0.3f), m_TextureCactus);
		//Engine::Renderer2D::DrawRotatedQuad(glm::vec3(m_Position.x - sin(timer), m_Position.y, 0.0f), glm::vec2(1.0f), glm::radians(sin(timer * 3) * 10), m_Texture, m_Color);
		

		
		/*
		m_Particle.ColorBegin = m_Color;
		m_Particle.ColorEnd = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
		if (Engine::Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = Engine::Input::GetMousePosition();
			auto width = Engine::Application::Get().GetWindow().GetWidth();
			auto height = Engine::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();

			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y, 0.1f };
			for (int i = 0; i < 2; i++)
			{
				m_ParticleSystem.Emit(m_Particle);
			}
		

		}
		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
		*/
	}
	void OnImGuiRender() override
	{
		
		ImGui::Begin("Settings");


		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));


		auto stats = Engine::Renderer2D::GetStats();
		ImGui::Text("%dFPS", m_FPS);
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Darw Calls:%d", stats.DrawCalls);
		ImGui::Text("Quads Count:%d", stats.QuadCount);
		ImGui::Text("Vertices Count:%d", stats.GetTotalVertexCount());
		ImGui::Text("Indices Count:%d", stats.GetTotalIndexCount());

		

		ImGui::End();
	}
	void OnEvent(Engine::Event& event) override
	{
		m_CameraController.OnEvent(event);
		//ENGINE_TRACE("{0}", event.ToString());
	}
private:
	
	std::shared_ptr<Engine::Texture2D> m_Texture;
	std::shared_ptr<Engine::Texture2DArray> m_SpriteSheet;;

	Engine::OrthographicCameraController m_CameraController;	
	float m_MoveSpeed = 0.5f;
	glm::vec4 m_Color = glm::vec4(1.0f);
	glm::vec2 m_Position = glm::vec2(0.0f);

	unsigned int m_FPS = 60;

	//Engine::ParticleSystem m_ParticleSystem;
	//Engine::ParticleProps m_Particle;
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