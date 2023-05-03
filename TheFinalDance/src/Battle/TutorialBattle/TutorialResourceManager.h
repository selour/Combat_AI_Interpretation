#pragma once
#include "Core/ResourceManager.h"
class TutorialResourceManager : public ResourceManager
{
public:
	virtual void Init() override
	{
		auto shaders = GetShaderLibrary();
		auto soundSources = GetSoundSourceLibrary();
		auto textures = GetTextureLibrary();
		shaders->Load("BeatShader", "assets/shaders/BeatShader.glsl");
		shaders->Load("Block", "assets/shaders/Block.glsl");
		shaders->Load("heart", "assets/shaders/heart.glsl");
		shaders->Load("Post", "assets/shaders/Post.glsl");
		shaders->Load("FBO", "assets/shaders/FBO.glsl");
		shaders->Load("Bright", "assets/shaders/BrightColor.glsl");
		shaders->Get("heart")->SetInteger("u_Texture0", 0, true);
		shaders->Get("Post")->SetInteger("u_Texture0", 0, true);
		shaders->Get("FBO")->SetInteger("u_Texture0", 0, true);
		shaders->Get("Bright")->SetInteger("u_Texture0", 0, true);

		soundSources->Load("tutorial_metronome_start", "assets/audio/tutorial_metronome/tutorial_metronome_start.wav");
		soundSources->Load("tutorial_metronome_loop", "assets/audio/tutorial_metronome/tutorial_metronome_loop.wav");
		soundSources->Load("tutorial_startup", "assets/audio/tutorial_metronome/tutorial_startup.wav");
		soundSources->Load("bell", "assets/audio/tutorial_metronome/Bell.wav");
		soundSources->Load("ddddance", "assets/audio/ddddance_time.wav");
		soundSources->Load("hat", "assets/audio/hat.wav");
		soundSources->Load("clap", "assets/audio/clap.wav");
		soundSources->Load("swoosh", "assets/audio/swoosh.wav");
		soundSources->Load("solid", "assets/audio/solid.wav");
		soundSources->Load("error", "assets/audio/error.wav");
		soundSources->Get("bell")->SetVolume(0.5f);
		soundSources->Get("ddddance")->SetVolume(0.5f);
		soundSources->Get("hat")->SetVolume(0.2f);
		soundSources->Get("clap")->SetVolume(0.3f);
		soundSources->Get("error")->SetVolume(0.5f);

		textures->Load("number", "assets/textures/number.png", 10, 1);
		textures->Load("metronome", "assets/textures/metronome.png", 1, 1);
		textures->Load("heart", "assets/textures/heart.png", 5, 1);
		textures->Load("player", "assets/textures/player.png", 3, 1);
		textures->Load("dancetime", "assets/textures/DanceTime.png", 2, 1);

		textures->Load("metronome_ui", "assets/textures/metronome_ui.png", 3, 2);
	}
};
