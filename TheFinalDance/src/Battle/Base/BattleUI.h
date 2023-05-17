#pragma once
#include "Core/ObjectManager.h"
#include "Core/Transform.h"
class BattleUI : public GameObject
{
public:
	BattleUI()
	{
		m_Background.SetFather(&m_Main);
		m_Character.SetFather(&m_Main);
		m_Frame.SetFather(&m_Main);
	}
protected:
	Transform m_Main;
	Transform m_Background;
	Transform m_Character;
	Transform m_Frame;

};