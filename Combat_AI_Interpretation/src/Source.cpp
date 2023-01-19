#include "Engine.h"

class Game : public Engine::Application
{
public:
	Game() {};
	~Game() {};
};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}