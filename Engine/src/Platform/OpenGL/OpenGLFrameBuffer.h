#pragma once
#include "Engine/Renderer/FrameBuffer.h"
namespace Engine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Init();

		virtual void Bind() override;
		virtual void UnBind()override;

		virtual void BindColorAttachment(unsigned slot = 0) const override;

		virtual const unsigned int GetColorAttachment() const override { return m_ColorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		unsigned int m_FBO;
		unsigned int m_ColorAttachment;
		FrameBufferSpecification m_Specification;
	};
}


