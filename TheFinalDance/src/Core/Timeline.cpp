#include "Timeline.h"



//------------------------------Track----------------------------------------

Track::Track(const std::string text, std::shared_ptr<SoundSource> soundSoure)
	:m_Lenght(text.length()),m_Text(text), m_SoundSoure(soundSoure)
{
}

void Track::Play()
{
	m_Index++;
	m_Index %= m_Lenght;
	if (m_Text[m_Index] == '1')
	{
		SoundEngine::Play2D(m_SoundSoure);
	}
}




//-------------------------------Phase-------------------------------------


void Phase::Update()
{
	if (m_TrackCount != 0)
	{
		for (int i = 0; i < m_TrackCount; i++)
		{
			m_Tracks[i].Play();
		}
	}
}

void Phase::AddTracks(const std::string text, std::shared_ptr<SoundSource> soundSoure)
{
	m_Tracks.push_back(Track(text, soundSoure));
	m_TrackCount++;
}
//-------------------------------Timeline-------------------------------------


void Timeline::StateUpate()
{
	m_State++;
	if (m_State == m_PhaseCount)
		m_IsActivate = false;
}

void Timeline::BeatUpdate()
{
	if(m_IsActivate)
		m_Phases[m_State]->Update();
}


const bool Timeline::IsActivate() const
{
	return m_IsActivate;
}

std::shared_ptr<Phase> Timeline::addPhase()
{
	m_PhaseCount++;
	auto phase = std::make_shared<Phase>();
	m_Phases.push_back(phase);
	return phase;
}

