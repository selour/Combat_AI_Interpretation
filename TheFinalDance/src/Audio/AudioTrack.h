#pragma once
#include "SoundEngine.h"
#include <vector>

class Pattern
{
public:
	Pattern(std::string text, std::shared_ptr<SoundSource> soundSoure);
	void Activate(int begin);
	void Update(int beat);
	bool IsActivate();
private:

	void Play();
	bool m_IsActivate = false;
	int m_MaxBeatCount = 8;
	int m_beginBeat = 0;
	int m_CurrentBeat = -1;
	std::string m_Text;
	std::shared_ptr<SoundSource> m_SoundSoure;
};

class Track
{
public:
	Track();
	void SetState(int state);
	void Update(int beatCount);
	bool IsActivate();

	void addPattern(std::string text, std::shared_ptr<SoundSource> soundSoure);
private:
	int m_Change = -1;
	int m_State = -1;
	std::vector<std::shared_ptr<Pattern>> m_Patterns;
};

