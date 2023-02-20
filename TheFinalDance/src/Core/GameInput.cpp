#include "GameInput.h"


GameInput* GameInput::s_Instance = GameInput::Init();

bool GameInput::IsUpKeyPoressed()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[1]);
}

bool GameInput::IsDownKeyPoressed()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[2]);
}

bool GameInput::IsLeftKeyPoressed()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[3]);
}

bool GameInput::IsRightKeyPoressed()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[4]);
}

bool GameInput::IsInteractiveKeyPoressed()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[0]);
}

bool GameInput::IsUpKeyDown()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[1])&& !s_Instance->m_IsKeyPoressed[1];
}

bool GameInput::IsDownKeyDown()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[2]) && !s_Instance->m_IsKeyPoressed[2];
}

bool GameInput::IsLeftKeyDown()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[3]) && !s_Instance->m_IsKeyPoressed[3];
}

bool GameInput::IsRightKeyDown()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[4]) && !s_Instance->m_IsKeyPoressed[4];
}

bool GameInput::IsInteractiveKeyDown()
{
	return Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[0]) && !s_Instance->m_IsKeyPoressed[0];
}

bool GameInput::IsUpKeyRelease()
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[1]) && s_Instance->m_IsKeyPoressed[1];
}

bool GameInput::IsDownKeyRelease()
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[2]) && s_Instance->m_IsKeyPoressed[2];
}

bool GameInput::IsLeftKeyRelease()
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[3]) && s_Instance->m_IsKeyPoressed[3];
}

bool GameInput::IsRightKeyRelease()
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[4]) && s_Instance->m_IsKeyPoressed[4];
}

bool GameInput::IsInteractiveKeyRelease()
{
	return !Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[0]) && s_Instance->m_IsKeyPoressed[0];
}

void GameInput::UpdateKeyEvent()
{
	if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[0]))
		s_Instance->m_IsKeyPoressed[0] = true;
	else
		s_Instance->m_IsKeyPoressed[0] = false;
	if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[1]))
		s_Instance->m_IsKeyPoressed[1] = true;
	else
		s_Instance->m_IsKeyPoressed[1] = false;
	if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[2]))
		s_Instance->m_IsKeyPoressed[2] = true;
	else
		s_Instance->m_IsKeyPoressed[2] = false;
	if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[3]))
		s_Instance->m_IsKeyPoressed[3] = true;
	else
		s_Instance->m_IsKeyPoressed[3] = false;
	if (Engine::Input::IsKeyPoressed(s_Instance->m_KeyCode[4]))
		s_Instance->m_IsKeyPoressed[4] = true;
	else
		s_Instance->m_IsKeyPoressed[4] = false;
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
