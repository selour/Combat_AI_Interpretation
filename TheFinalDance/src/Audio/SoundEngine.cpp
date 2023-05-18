#include "SoundEngine.h"
#include "Engine/Core/Core.h"
irrklang::ISoundEngine* SoundEngine::s_SoundEngine = irrklang::createIrrKlangDevice();


//-------------------------SoundSource-----------------------------------------------
SoundSource::SoundSource(const char* path)
	:m_SoundSource(SoundEngine::s_SoundEngine->addSoundSourceFromFile(path))
{
}

SoundSource::~SoundSource()
{
	SoundEngine::s_SoundEngine->removeSoundSource(m_SoundSource);
}

void SoundSource::SetVolume(float value)
{
	m_SoundSource->setDefaultVolume(value);
}

float SoundSource::GetPlayLenth()
{
	return m_SoundSource->getPlayLength()/1000.0f;
}

ISoundSource* SoundSource::GetSoundSource() const
{
	return m_SoundSource;
}


void SoundSourceLibrary::Add(const std::shared_ptr<SoundSource>& soundSource, const std::string& name)
{
	ENGINE_ASSERT(!IsExists(name), "SoundSource already exists!");
	m_SoundSources[name] = soundSource;
}


std::shared_ptr<SoundSource> SoundSourceLibrary::Load(const std::string& name, const std::string& filePath)
{
	auto ss = std::make_shared<SoundSource>(filePath.c_str());
	Add(ss, name);
	return ss;
}

std::shared_ptr<SoundSource> SoundSourceLibrary::Get(const std::string& name)
{
	ENGINE_ASSERT(IsExists(name), "SoundSource not found!");
	return m_SoundSources[name];
}

bool SoundSourceLibrary::IsExists(const std::string& name) const
{
	return m_SoundSources.find(name) != m_SoundSources.end() && !m_SoundSources.empty();
}
