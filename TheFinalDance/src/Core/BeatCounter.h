#pragma once
#include "Engine.h"
class BeatCounter
{
public:
	BeatCounter();
	void Clear();
	void Update(Engine::TimeStep ts);

	int GetBPM()
	{
		return m_Bpm;
	}
	void SetBPM(int bpm)
	{
		m_Bpm = bpm;
	}
	int GetCounter()
	{
		return m_BeatCounter;
	}
	float GetTime()
	{
		return m_Time;
	}
private:
	int m_Bpm;
	float m_Time;
	int m_BeatCounter;
};

