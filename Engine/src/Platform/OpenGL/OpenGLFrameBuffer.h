#pragma once
#include "Engine/Renderer/FrameBuffer.h"
#include <vector>
namespace Engine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const ColorAttachmentSpecification& spec);
		OpenGLFrameBuffer(const ColorAttachmentSpecification& cas, const RenderBufferSpecification& rbs);
		virtual ~OpenGLFrameBuffer();

		void Init();

		virtual void Bind() override;
		virtual void UnBind()override;

		virtual void BindColorAttachment(unsigned slot = 0) const override;

		virtual const unsigned int GetColorAttachment() const override { return m_ColorAttachment; }
		virtual const ColorAttachmentSpecification& GetColorAttachmentSpec() const override { return m_ColorAttachmentSpec; }
	private:
		unsigned int m_FBO;
		unsigned int m_ColorAttachment;
		bool m_HasRBO;
		ColorAttachmentSpecification m_ColorAttachmentSpec;
		RenderBufferSpecification m_RenderBufferSpec;
	};


	class OpenGLMRTFrameBuffer : public MRTFrameBuffer
	{
	public:
		OpenGLMRTFrameBuffer(const ColorAttachmentSpecification* cas, unsigned amount, const RenderBufferSpecification* rbs);
		virtual ~OpenGLMRTFrameBuffer();

		void Init();

		virtual void Bind() override;
		virtual void UnBind()override;

		virtual void BindColorAttachment(unsigned slot = 0) const override;
		virtual void BindColorAttachment(unsigned slot , unsigned index ) const override;
		virtual const unsigned int GetColorAttachment(unsigned index) const override { return m_ColorAttachments[index]; }
		virtual const unsigned int GetColorAttachmentSize() const override;

		virtual const ColorAttachmentSpecification& GetSpecification(unsigned index) const override { return m_ColorAttachmentSpec[index]; }
	private:
		unsigned int m_FBO;
		unsigned int m_Amount;
		std::vector<unsigned int> m_ColorAttachments;
		bool m_HasRBO;
		std::vector <ColorAttachmentSpecification> m_ColorAttachmentSpec;
		RenderBufferSpecification m_RenderBufferSpec;
	};
}


