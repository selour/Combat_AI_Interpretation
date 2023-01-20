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

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};
	//��������ʵ�ʵ���Ϸ��
	Application* CreateApp();
}


