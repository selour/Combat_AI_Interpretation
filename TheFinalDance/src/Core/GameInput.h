#pragma once
#include "Engine.h"
class GameInput
{
public:
	//����ס
	static bool IsUpKeyPoressed();
	static bool IsDownKeyPoressed();
	static bool IsLeftKeyPoressed();
	static bool IsRightKeyPoressed();
	static bool IsInteractiveKeyPoressed();
	//������
	static bool IsUpKeyDown();
	static bool IsDownKeyDown();
	static bool IsLeftKeyDown();
	static bool IsRightKeyDown();
	static bool IsInteractiveKeyDown();
	//���ɿ�
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

