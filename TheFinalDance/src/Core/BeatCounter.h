#pragma once
#include "Object.h"
#include <memory>
#include <vector>

enum EventType
{
	Awake = 0, Destroy = 1, Jump = 2
		
};
struct BeatEvent
{
	BeatEvent(EventType type, unsigned int beat, unsigned int value)
		:Type(type),Beat(beat),Value(value)
	{}
	EventType Type;
	unsigned int Beat;
	unsigned int Value;
};
class TimeLine
{
public:
	void AddEvent(EventType type, unsigned int beat, unsigned int value);
	void AddObject(Object* object)
	{
		m_Objects.push_back(object);
	}
	void Update();
	void OnBeat();

	unsigned int GetCounter()
	{
		return m_BeatCount;
	}

private:
	bool m_OnBeat = false;
	unsigned int m_BeatCount = 0;
	unsigned int m_index = 0;
	std::vector<BeatEvent> m_EventList;
	std::vector<Object*> m_Objects;
};

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
	
	float GetTime()
	{
		return m_Time;
	}

	void AddObject(Object* object)
	{
		m_Objects.push_back(object);
	}

	TimeLine* GetTimeLine()
	{
		return &m_TimeLine;
	}
private:
	int m_Bpm;
	float m_Time;
	std::vector<Object*> m_Objects;
	TimeLine m_TimeLine;
};