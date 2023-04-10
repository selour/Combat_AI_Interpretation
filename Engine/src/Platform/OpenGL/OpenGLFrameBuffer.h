#pragma once
#include "Engine/Renderer/FrameBuffer.h"
#include <vector>
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


	class OpenGLMRTFrameBuffer : public MRTFrameBuffer
	{
	public:
		OpenGLMRTFrameBuffer(const FrameBufferSpecification& spec, unsigned amount);
		virtual ~OpenGLMRTFrameBuffer();

		void Init();

		virtual void Bind() override;
		virtual void UnBind()override;

		virtual void BindColorAttachment(unsigned slot = 0) const override;
		virtual void BindColorAttachment(unsigned slot , unsigned index ) const override;
		virtual const unsigned int GetColorAttachmentSize() const override;

		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		unsigned int m_FBO;
		unsigned int m_Amount;
		std::vector<unsigned int> m_ColorAttachments;
		FrameBufferSpecification m_Specification;
	};
}


