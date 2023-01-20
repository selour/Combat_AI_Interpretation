#include "Engine.h"

class Game : public Engine::Application
{

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}