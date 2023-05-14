#pragma once
#include "Engine.h"
enum InputType
{
	InteractiveKey = 0, UpKey = 1, DownKey = 2, LeftKey = 3, RightKey = 4
};
class GameInput
{
public:
	//����ס
	static bool IsKeyPoressed(InputType type);
	
	//������
	static bool IsKeyDown(InputType type);
	//��������
	static bool IsOnlyKeyDown(InputType type);
	//���ɿ�
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