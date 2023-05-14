#pragma once
#include "Engine.h"
enum InputType
{
	InteractiveKey = 0, UpKey = 1, DownKey = 2, LeftKey = 3, RightKey = 4
};
class GameInput
{
public:
	//键按住
	static bool IsKeyPoressed(InputType type);
	
	//键按下
	static bool IsKeyDown(InputType type);
	//单键按下
	static bool IsOnlyKeyDown(InputType type);
	//键松开
	static bool IsKeyRelease(InputType type);
	
	static void UpdateKeyEvent();
private:
	GameInput();
	unsigned int m_KeyCode[5];
	bool m_IsKeyPoressed[5];

	static GameInput* Init();
	static GameInput* s_Instance;
};

class InputLayer : public Engine::Layer
{
public:
	InputLayer()
		:Layer("Input")
	{
	}
	void OnUpdate(Engine::TimeStep ts) override
	{
		GameInput::UpdateKeyEvent();
	}
};