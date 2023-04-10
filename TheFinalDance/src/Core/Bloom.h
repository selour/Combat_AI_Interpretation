#pragma once
#include "Engine.h"
class Bloom
{
public:
	Bloom();
	void Begin() const;
	void End();
	void Render() const;

	float* GetExposure()
	{
		return &m_Exposure;
	}
private:
	unsigned int m_Amount = 10;
	float m_Exposure = 0.5f;
	bool m_Horizontal = true;
	std::shared_ptr <Engine::MRTFrameBuffer> m_MTRFBO;
	std::shared_ptr <Engine::FrameBuffer> m_FBOs[2];


	std::shared_ptr <Engine::Shader> m_ShaderBlur;
	std::shared_ptr <Engine::Shader> m_ShaderBloom;
};

