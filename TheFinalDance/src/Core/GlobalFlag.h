#pragma once
class GlobalFlag
{
public:

	inline static bool ShouldInBattle()
	{
		return s_Flags->m_ShouldInBattle;
	}
	inline static void SetShouldInBattle(bool flag)
	{
		s_Flags->m_ShouldInBattle = flag;
	}

	inline static bool InBattle()
	{
		return s_Flags->m_InBattle;
	}
	inline static void SetInBattle(bool flag)
	{
		s_Flags->m_InBattle = flag;
	}
	inline static bool BattleWin()
	{
		return s_Flags->m_BattleWin;
	}
	inline static void SetBattleWin(bool flag)
	{
		s_Flags->m_BattleWin = flag;
	}
	inline static bool ShouldExitBattle()
	{
		return s_Flags->m_ShouldExitBattle;
	}
	inline static void SetShouldExitBattle(bool flag)
	{
		s_Flags->m_ShouldExitBattle = flag;
	}
private:
	GlobalFlag()
	{
	}
	static GlobalFlag* s_Flags;
	bool m_ShouldInBattle = false;
	bool m_InBattle = false;
	bool m_BattleWin = false;
	bool m_ShouldExitBattle = false;
};


