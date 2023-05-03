#pragma once
#include "Engine.h"
#include "Core/Object.h"
class Bloom : public PostObject
{
public:
	Bloom();
	virtual void Bind() override;
	virtual void UnBind() override;
	//virtual void Render() override;
	void OnImGuiRender();
	void SetExposure(float exposure)
	{
		m_Exposure = exposure;
	}
private:
	float m_Exposure = 1.0f;
	bool m_Horizontal = true;
	std::shared_ptr <Engine::MRTFrameBuffer> m_MTRFBO;
	std::shared_ptr <Engine::FrameBuffer> m_FBOs[3][2];


	std::shared_ptr <Engine::Shader> m_ShaderBlur;
	std::shared_ptr <Engine::Shader> m_ShaderBloom;
	Engine::ColorAttachmentSpecification m_BlurFBSpec[3];
};

