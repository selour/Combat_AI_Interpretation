#include "GameInput.h"


GameInput* GameInput::s_Instance = GameInput::Init();


bool GameInput::IsKeyPoressed(InputType type)
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[type]);
}

bool GameInput::IsKeyDown(InputType type)
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[type]) && !s_Instance->m_IsKeyPoressed[type];
}
bool GameInput::IsOnlyKeyDown(InputType type)
{
	bool flag = true;
	for (int i = 0; i < 5; i++)
	{
		if((int)type == i)
		{
			flag = flag && IsKeyDown((InputType)i);
		}
		else
		{
			flag = flag && !IsKeyDown((InputType)i);
		}
	}
	return false;
}
bool GameInput::IsKeyRelease(InputType type)
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[type]) && s_Instance->m_IsKeyPoressed[type];
}

void GameInput::UpdateKeyEvent()
{
	for (int i = 0; i < 5; i++)
	{
		if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[i]))
			s_Instance->m_IsKeyPoressed[i] = true;
		else
			s_Instance->m_IsKeyPoressed[i] = false;
	}
}

GameInput::GameInput()
	:m_KeyCode{ ENGINE_KEY_SPACE, ENGINE_KEY_W, ENGINE_KEY_S, ENGINE_KEY_A, ENGINE_KEY_D }, m_IsKeyPoressed{ false, false, false, false, false }
{
}

GameInput* GameInput::Init()
{
	if(s_Instance == nullptr)
	return new GameInput();
}
