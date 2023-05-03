#include "Engine.h"
#include "EnterPoint.h"
#include "imgui.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/GameLayer.h"
//#include "Core/BattleLayer.h"
#include "Core/GameInput.h"

class Game : public Engine::Application
{
public:
	Game()
	{
		//AppPushLayer(new TestLayer());
		AppPushLayer(new GameLayer());
		AppPushOverlay(new InputLayer());
	}

	~Game()
	{
	}

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}