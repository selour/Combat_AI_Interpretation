#pragma once
#include "Engine/Core.h"
#include "Engine/Window.h"
namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};
	//将定义在实际的游戏中
	Application* CreateApp();
}


