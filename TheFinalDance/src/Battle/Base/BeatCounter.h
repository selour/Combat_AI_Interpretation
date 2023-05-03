#pragma once
#include "Engine.h"
#include "Core/GameEvent.h"
#include "Core/Object.h"
#include "imgui.h"
class BeatCounter : public GameObject
{
public:

	BeatCounter(int bpm = 100)
		:m_StartUpFlag(true), m_DelayTime(60.0f/(float)bpm), m_Timer(0)
	{
	}
	virtual void Update(float ts) override
	{
		if (m_StartUpFlag)
		{
			m_Timer += ts;
			if (m_Timer >= m_DelayTime)
			{
				OnBeat();
				m_Timer -= m_DelayTime;
			}

		}
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("BeatCounter");
		ImGui::Text("switch:%d", m_StartUpFlag);
		ImGui::Text("Bpm:%.2f", 60.0f / m_DelayTime);
		ImGui::Text("Time:%.2f", m_Timer);
		ImGui::End();
	}
	void Open()
	{
		m_StartUpFlag = true;
	}
	void Close()
	{
		m_StartUpFlag = false;
	}
	void Clear()
	{
		m_Timer = 0;
	}
	void SetBPM(int bpm)
	{
		m_Timer = 0;
		m_DelayTime = 60.0f / (float)bpm;
	}
	void AddDelegate(std::function<void()> func)
	{
		OnBeat += func;
	}
private:
	bool m_StartUpFlag = false;
	float m_DelayTime;
	float m_Timer;
	GameEvent<void()> OnBeat;

};

