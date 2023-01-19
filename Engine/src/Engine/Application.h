#pragma once

#include "Core.h"
namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};
	//将定义在实际的游戏中
	Application* CreateApp();
}


