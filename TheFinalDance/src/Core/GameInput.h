#pragma once
#include "Engine.h"
class GameInput
{
public:
	//键按住
	static bool IsUpKeyPoressed();
	static bool IsDownKeyPoressed();
	static bool IsLeftKeyPoressed();
	static bool IsRightKeyPoressed();
	static bool IsInteractiveKeyPoressed();
	//键按下
	static bool IsUpKeyDown();
	static bool IsDownKeyDown();
	static bool IsLeftKeyDown();
	static bool IsRightKeyDown();
	static bool IsInteractiveKeyDown();
	//键松开
	static bool IsUpKeyRelease();
	static bool IsDownKeyRelease();
	static bool IsLeftKeyRelease();
	static bool IsRightKeyRelease();
	static bool IsInteractiveKeyRelease();


	static void UpdateKeyEvent();
private:
	GameInput();
	unsigned int m_KeyCode[5];
	bool m_IsKeyPoressed[5];

	static GameInput* Init();
	static GameInput* s_Instance;
};

