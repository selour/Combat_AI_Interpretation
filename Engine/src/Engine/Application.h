#pragma once
#include "Engine/Core.h"
#include "Engine/Window.h"
#include "Events/WindowEvent.h"
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
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};
	//��������ʵ�ʵ���Ϸ��
	Application* CreateApp();
}


