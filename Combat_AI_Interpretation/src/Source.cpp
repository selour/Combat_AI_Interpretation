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
		:Layer("Test"), m_Run(6, true), m_CameraController(1280.0f / 720.0f, true)
	{
	}
	void OnAttach()
	{
		//读取纹理
		m_Texture = Engine::Texture2DArray::Create("assets/textures/eye.png", 1, 1);
		m_SpriteSheet = Engine::Texture2DArray::Create("assets/textures/run.png", 6, 1);
		//创建帧缓冲
		Engine::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_FrameBuffer = Engine::FrameBuffer::Create(fbSpec);
		//动画设置
		m_Run.SetLoop(true);
		m_Run.AutoGenerateFrames(0, 0.1);
		
		//设置粒子
		m_Particle.ColorBegin = m_Color;
		m_Particle.ColorEnd = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
		
		m_Particle.SizeBegin = 0.1f;
		m_Particle.SizeEnd = 0.0f;

		m_Particle.LifeTime = 0.5f;
		m_Particle.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Particle.VelocityVariation = glm::vec3(1.0f, 1.0f, 0.0f);
		m_Particle.Position = glm::vec3(0.0f, 0.0f, 0.1f);
		

		m_EyeParticle.ColorBegin = m_Color;
		m_EyeParticle.ColorEnd = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);

		m_EyeParticle.SizeBegin = 1.0f;
		m_EyeParticle.SizeEnd = 0.0f;

		m_EyeParticle.LifeTime = 0.5f;
		m_EyeParticle.Velocity = glm::vec3(0.0f, 1.0f, 0.0f);
		m_EyeParticle.VelocityVariation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_EyeParticle.Position = glm::vec3(0.0f, 0.0f, -0.1f);
	}

	void OnUpdate(Engine::TimeStep ts) override
	{
		m_FPS = 1.0f / ts;
		m_CameraController.OnUpdate(ts);

		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_LEFT))
		{
			m_face = 1;
			m_Position.x -= m_MoveSpeed * ts;
		}
			
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_RIGHT))
		{
			m_face = -1;
			m_Position.x += m_MoveSpeed * ts;
		}
			
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_UP))
			m_Position.y += m_MoveSpeed * ts;
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_DOWN))
			m_Position.y -= m_MoveSpeed * ts;



		timer += ts * 2;
		

		m_FrameBuffer->Bind();
		{
			Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
			Engine::RendererCommand::Clear();

			Engine::Renderer2D::ResetStats();
			Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

			glm::vec4 quadColor = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
			for (float y = -5.0f; y < 5.0f; y += 0.25f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.25f)
				{
					Engine::Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(0.23f), 0, quadColor);
				}
			}
			Engine::Renderer2D::EndScene();

			
			m_EyeParticle.ColorBegin = m_Color;
			m_EyeParticle.ColorEnd = glm::vec4(1.0f - m_Color.r, 1.0f - m_Color.g, 1.0f - m_Color.b, 1.0f);
			m_EyeParticle.Position = glm::vec3( - sin(timer), 0.0f, -0.5f);

			m_ParticleSystem.Emit(m_EyeParticle);
			m_ParticleSystem.OnUpdate(ts);
			m_ParticleSystem.OnRender(m_CameraController.GetCamera(), m_Texture);

			Engine::Renderer2D::BeginScene(m_CameraController.GetCamera(), m_Texture);
			
			Engine::Renderer2D::DrawQuad(glm::vec2(- sin(timer), 0.0f), glm::vec2(1.0f), glm::radians(sin(timer * 3) * 10), m_Color);
			
			Engine::Renderer2D::EndScene();

			
			Engine::Renderer2D::BeginScene(m_CameraController.GetCamera(), m_SpriteSheet);
			m_Run.OnUpdate(ts);
			Engine::Renderer2D::DrawQuad(m_Position, glm::vec2(m_face * 0.3f, 0.3f), 0, glm::vec4(1.0f), m_Run.GetTexCoordZs());

			Engine::Renderer2D::EndScene();
		}
		m_FrameBuffer->UnBind();

		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();
		Engine::RendererPostProcessing::Draw(m_FrameBuffer);

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
		/*
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::End();
		*/
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
		
		ImGui::Begin("Viewport");
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		unsigned int textureID = m_FrameBuffer->GetColorAttachment();
		ImGui::Image((void*)textureID, ImVec2{ 1280/4,720/4 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();


	

	}
	void OnEvent(Engine::Event& event) override
	{
		m_CameraController.OnEvent(event);
		//ENGINE_TRACE("{0}", event.ToString());
	}
private:
	
	std::shared_ptr<Engine::Texture2DArray> m_Texture;
	std::shared_ptr<Engine::Texture2DArray> m_SpriteSheet;
	std::shared_ptr<Engine::FrameBuffer> m_FrameBuffer;

	Engine::Animation2D m_Run;
	Engine::OrthographicCameraController m_CameraController;	

	float m_MoveSpeed = 0.5f;
	glm::vec4 m_Color = glm::vec4(1.0f);
	glm::vec2 m_Position = glm::vec2(0.0f);
	int m_face = 1;
	unsigned int m_FPS = 60;

	Engine::ParticleSystem m_ParticleSystem;
	Engine::ParticleProps m_Particle;
	Engine::ParticleProps m_EyeParticle;
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