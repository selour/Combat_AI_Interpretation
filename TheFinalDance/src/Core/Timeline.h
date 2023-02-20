#pragma once
#include "Audio/SoundEngine.h"
#include <vector>
class Track
{
public:
	Track(const std::string text, std::shared_ptr<SoundSource> soundSoure);
	void Play();
private:
	int m_Index = -1;
	int m_Lenght;
	std::string m_Text;
	std::shared_ptr<SoundSource> m_SoundSoure;
};

class Phase
{
public:
	void Update();
	void AddTracks(const std::string text, std::shared_ptr<SoundSource> soundSoure);
private:

	
	int m_TrackCount = 0;
	std::vector<Track> m_Tracks;
	
};

class Timeline
{
public:
	Timeline()
		:m_IsActivate(true), m_State(0), m_PhaseCount(0)
	{
	}
	void StateUpate();
	void BeatUpdate();

	const bool IsActivate() const;

	std::shared_ptr<Phase> addPhase();
private:
	bool m_IsActivate;
	int m_State;
	int m_PhaseCount;
	std::vector<std::shared_ptr<Phase>> m_Phases;
};

