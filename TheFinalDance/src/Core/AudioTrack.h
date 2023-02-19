#pragma once
#include "SoundEngine.h"
#include <vector>

class Pattern
{
public:
	Pattern(std::string text, std::shared_ptr<SoundSource> soundSoure);
	void Activate(int begin);
	void Update(int beat);
	bool IsEnd();
private:

	void Play();

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
	bool IsPlay();

	void addPattern(std::string text, std::shared_ptr<SoundSource> soundSoure);
private:
	bool m_Change = false;
	int m_State = -1;
	std::vector<std::shared_ptr<Pattern>> m_Patterns;
};

