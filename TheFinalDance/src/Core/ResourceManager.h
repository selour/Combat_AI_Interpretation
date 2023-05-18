#pragma once
#include "Engine.h"
#include "Audio/SoundEngine.h"
class ResourceManager
{
public:
	virtual void Init() = 0;
	SoundSourceLibrary* GetSoundSourceLibrary()
	{
		return &m_SoundSources;
	}
	Engine::ShaderLibrary* GetShaderLibrary()
	{
		return &m_Shaders;
	}
	Engine::Texture2DArrayLibrary* GetTextureLibrary()
	{
		return &m_Textures;
	}
	
private:
	SoundSourceLibrary m_SoundSources;
	Engine::ShaderLibrary m_Shaders;
	Engine::Texture2DArrayLibrary m_Textures;
	
	
};

