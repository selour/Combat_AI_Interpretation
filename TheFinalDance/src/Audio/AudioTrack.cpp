#include "AudioTrack.h"



//-----------------------------Pattern--------------------------------------
Pattern::Pattern(std::string text, std::shared_ptr<SoundSource> soundSoure)
	:m_MaxBeatCount(text.length()),m_Text(text), m_SoundSoure(soundSoure)
{
	
}

void Pattern::Activate(int begin)
{
	m_IsActivate = true;
	m_beginBeat = begin;
	m_CurrentBeat = -1;
}

void Pattern::Update(int beat)
{
	if (m_CurrentBeat != m_MaxBeatCount)
	{
		int current = beat - m_beginBeat;
		if (current != m_CurrentBeat)
		{
			m_CurrentBeat = current;
			Play();
		}
	}
	else
	{
		m_IsActivate = false;
	}

}

bool Pattern::IsActivate()
{
	
	return m_IsActivate;
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
	:m_Change(-1), m_State(-1)
{

}
void Track::SetState(int state)
{
	m_Change = state;

}

void Track::Update(int beatCount)
{
	if (m_State != -1)
	{
		if (!IsActivate())
		{
			if (m_Change != m_State)
			{
				m_State = m_Change;
				m_Patterns[m_State]->Activate(beatCount);
				m_Patterns[m_State]->Update(beatCount);
			}
			else
			{
				m_Change = -1;
				m_State = -1;
			}
		}
		else
		{
			m_Patterns[m_State]->Update(beatCount);
		}
		
		
	}
	else
	{
		if (m_Change != m_State)
		{
			m_State = m_Change;
			m_Patterns[m_State]->Activate(beatCount);
			m_Patterns[m_State]->Update(beatCount);
		}
	}
	
}

bool Track::IsActivate()
{
	return (m_State != -1) && m_Patterns[m_State]->IsActivate();
}

void Track::addPattern(std::string text, std::shared_ptr<SoundSource> soundSoure)
{
	auto p = std::make_shared<Pattern>(text, soundSoure);
	m_Patterns.push_back(p);
}
