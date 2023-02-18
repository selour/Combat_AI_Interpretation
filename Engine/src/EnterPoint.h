#pragma once
#include "Engine.h"

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApp();


int main(int argc, char** argv)
{
	//初始化日志系统
	Engine::Log::Init();
	ENGINE_CORE_WARN("Initialized Log!");
	ENGINE_INFO("Hello World!");
	
	auto app = Engine::CreateApp();
	app->Run();
	delete app;
}

#endif