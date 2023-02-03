#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Core/Window.h"
#include "Engine/Events/WindowEvent.h"
#include "Engine/Core/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Camera.h"
namespace Engine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void AppPushLayer(Layer* layer);

		void AppPushOverlay(Layer* layer);

		inline Window& GetWindow() 
		{
			return *m_Window;
		}
		inline static Application& Get()
		{
			return *s_Instance;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);
		std::unique_ptr<Window> m_Window;
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;


		bool m_Running = true;//应用是否运行
		bool m_Minimized = false;//应用是否最小化


	};
	//将定义在实际的游戏中
	Application* CreateApp();
}


