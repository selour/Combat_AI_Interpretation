#pragma once
#include <irrKlang.h>
#include <memory>
#include <unordered_map>
#include <string>
using namespace irrklang;


class SoundSource
{
public:
	SoundSource(const char* path);
	~SoundSource();

	void SetVolume(float value);
	float GetPlayLenth();
	ISoundSource* GetSoundSource() const;
	
private:
	ISoundSource* m_SoundSource;
};

class SoundSourceLibrary
{
public:
	void Add(const std::shared_ptr<SoundSource>& soundSource, const std::string& name);
	std::shared_ptr<SoundSource> Load(const std::string& name, const std::string& filePath);
	std::shared_ptr<SoundSource> Get(const std::string& name);
	bool IsExists(const std::string& name) const;
private:
	std::unordered_map<std::string, std::shared_ptr<SoundSource>> m_SoundSources;
};

class SoundEngine
{
	friend class SoundSource;
public:
	inline static void Play2D(const char* path, bool loop = false)
	{
		s_SoundEngine->play2D(path, loop);
	}
	inline static void Play2D(std::shared_ptr<SoundSource> soundSource, bool loop = false)
	{
		s_SoundEngine->play2D(soundSource->GetSoundSource(), loop);
	}
	inline static void StopAllSound()
	{
		s_SoundEngine->stopAllSounds();
	}
	inline static void SetAllSoundsPaused(bool puased)
	{
		s_SoundEngine->setAllSoundsPaused(puased);

	}
	
private:
	SoundEngine()
	{
	}
	static ISoundEngine* s_SoundEngine;
};