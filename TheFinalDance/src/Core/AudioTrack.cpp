#include "AudioTrack.h"



//-----------------------------Pattern--------------------------------------
Pattern::Pattern(std::string text, std::shared_ptr<SoundSource> soundSoure)
	:m_MaxBeatCount(text.length()),m_Text(text), m_SoundSoure(soundSoure)
{
	
}

void Pattern::Activate(int begin)
{
	m_beginBeat = begin;
	m_CurrentBeat = -1;
}

void Pattern::Update(int beat)
{
	if (m_CurrentBeat != m_MaxBeatCount)
	{
		int current = (beat - m_beginBeat) % m_MaxBeatCount;
		if (current != m_CurrentBeat)
		{
			m_CurrentBeat = current;
			Play();
		}
	}

}

bool Pattern::IsEnd()
{
	
	return m_CurrentBeat == m_MaxBeatCount;
}
	
	

void Pattern::Play()
{
	if (m_Text[m_CurrentBeat] == '1')
	{
		SoundEngine::Play2D(m_SoundSoure);
	}
}





//------------------------------Track----------------------------------------
Track::Track()
	:m_Change(false), m_State(-1)
{

}
void Track::SetState(int state)
{
	m_State = state;
	m_Change = true;

}

void Track::Update(int beatCount)
{
	if (m_State != -1)
	{
		if (m_Change && (!IsPlay()))
		{
			m_Patterns[m_State]->Activate(beatCount);
		}
		m_Patterns[m_State]->Update(beatCount);
	}
	else
	{
		if (m_Change)
			m_Change = false;
	}
	
}

bool Track::IsPlay()
{
	return (m_State != -1) && !m_Patterns[m_State]->IsEnd();
}

void Track::addPattern(std::string text, std::shared_ptr<SoundSource> soundSoure)
{
	auto p = std::make_shared<Pattern>(text, soundSoure);
	m_Patterns.push_back(p);
}
