#pragma once
#include "Object.h"
#include <memory>
#include <vector>
class BeatCounter
{
public:
	BeatCounter();
	void Clear();
	void Update(float ts);

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

	void AddObject(Object* object)
	{
		m_Objects.push_back(object);
	}

private:
	int m_Bpm;
	float m_Time;
	int m_BeatCounter;
	std::vector<Object*> m_Objects;
};

