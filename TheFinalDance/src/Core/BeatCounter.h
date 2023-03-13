#pragma once
#include "Object.h"
#include <memory>
#include <vector>



class BeatCounter : public GameObject
{
public:
	BeatCounter(ObjectManager* objects);
	virtual void Reset() override;
	virtual void Update(float ts) override;
	
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

private:
	int m_Bpm;
	float m_Time;
	ObjectManager* m_Objects;
};