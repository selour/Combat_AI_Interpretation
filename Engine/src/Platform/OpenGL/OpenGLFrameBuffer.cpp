#include "stdafx.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
namespace Engine
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec)
	{
		Init();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FBO);
	}
	void OpenGLFrameBuffer::Init()
	{
		glCreateFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
			m_Specification.Width, m_Specification.Height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


		ENGINE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}
	void OpenGLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::BindColorAttachment(unsigned slot) const
	{
		glBindTextureUnit(slot, m_ColorAttachment);
	}




	OpenGLMRTFrameBuffer::OpenGLMRTFrameBuffer(const FrameBufferSpecification& spec, unsigned amount)
		:m_Amount(amount), m_Specification(spec)
	{
		Init();
	}

	OpenGLMRTFrameBuffer::~OpenGLMRTFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FBO);
	}

	void OpenGLMRTFrameBuffer::Init()
	{
		ENGINE_CORE_ASSERT(m_Amount < 32, "The number of color attachments exceeds the maximum limit!");
		glCreateFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);


		unsigned int colorAttachment[32];
		glCreateTextures(GL_TEXTURE_2D, m_Amount, colorAttachment);
		for (int i = 0; i < m_Amount; i++)
		{

			glBindTexture(GL_TEXTURE_2D, colorAttachment[i]);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F,
				m_Specification.Width, m_Specification.Height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachment[i], 0);
			m_ColorAttachments.push_back(colorAttachment[i]);
		}
		
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		unsigned int attachments[32];
		for (int i = 0; i < m_Amount; i++)
		{
			attachments[i] = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(m_Amount, attachments);



		ENGINE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLMRTFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void OpenGLMRTFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLMRTFrameBuffer::BindColorAttachment(unsigned slot) const
	{
		glBindTextureUnit(slot, m_ColorAttachments[slot]);
	}

	void OpenGLMRTFrameBuffer::BindColorAttachment(unsigned slot, unsigned index) const
	{
		glBindTextureUnit(slot, m_ColorAttachments[index]);
	}

	

	const unsigned int OpenGLMRTFrameBuffer::GetColorAttachmentSize() const
	{
		return m_ColorAttachments.size();
	}


}