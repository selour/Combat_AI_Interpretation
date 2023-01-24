#pragma once
#include "Engine/Core.h"
#include "Engine/Window.h"
#include "Events/WindowEvent.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
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
		std::unique_ptr<Window> m_Window;
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};
	//将定义在实际的游戏中
	Application* CreateApp();
}


