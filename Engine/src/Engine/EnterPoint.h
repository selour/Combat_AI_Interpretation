#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApp();
#include <iostream>
int main(int argc, char** argv)
{
	printf("hello world!\n");
	auto app = Engine::CreateApp();
	app->Run();
	delete app;
}

#endif