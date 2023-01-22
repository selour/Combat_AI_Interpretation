#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
	TestLayer()
		:Layer("Test")
	{}
	void OnUpdate() override
	{
		//ENGINE_INFO("TestLayer::Update");

	}
	void OnEvent(Engine::Event& event) override
	{
		ENGINE_TRACE("{0}", event.ToString());
	}
};

class Game : public Engine::Application
{
public:
	Game()
	{
		AppPushLayer(new TestLayer());
		AppPushOverlay(new Engine::ImGuiLayer());
	}

	~Game()
	{
	}

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}