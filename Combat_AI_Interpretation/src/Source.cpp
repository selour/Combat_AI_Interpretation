#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
	TestLayer()
		:Layer("Test")
	{}
	void OnUpdate() override
	{
		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_TAB))
			ENGINE_TRACE("Tab key is poressed!");

	}
	void OnImGuiRender() override
	{
		
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
	}

	~Game()
	{
	}

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}