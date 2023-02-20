#pragma once
#include "Timeline.h"
#include <memory>
class BeatCounter
{
public:
	BeatCounter(std::shared_ptr<Timeline> timeline);
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
private:
	int m_Bpm;
	float m_Time;
	int m_BeatCounter;
	std::shared_ptr<Timeline> m_Timeline;
};

