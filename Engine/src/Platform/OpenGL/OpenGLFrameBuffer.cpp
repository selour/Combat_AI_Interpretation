#include "stdafx.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
namespace Engine
{




	GLenum OpenGLEnum(TextureInternalFormat format)
	{
		switch (format)
		{
		case RGB4:	 return GL_RGB4;
		case RGB5:	 return GL_RGB5;
		case RGB8:	 return GL_RGB8;
		case RGB10:	 return GL_RGB10;
		case RGB12:	 return GL_RGB12;
		case RGB16:	 return GL_RGB16;
		case RGBA2:	 return GL_RGBA2;
		case RGBA4:	 return GL_RGBA4;
		case RGB5A1: return GL_RGB5_A1;
		case RGBA8:	 return GL_RGBA8;
		case RGB10A2:return GL_RGB10_A2;
		case RGBA12: return GL_RGBA12;
		case RGBA16: return GL_RGBA16;
		case RGBA32F:return GL_RGBA32F;
		case RGB32F: return GL_RGB32F;
		case RGBA16F:return GL_RGBA16F;
		case RGB16F: return GL_RGB16F;
		}
		return 0;
	}
	GLint OpenGLEnum(TextureFormat format)
	{
		switch (format)
		{
		case RED:  return GL_RED;
		case GREEN:return GL_GREEN;
		case BLUE:return GL_BLUE;
		case ALPHA:return GL_ALPHA;
		case RGB: return GL_RGB;
		case RGBA:return GL_RGBA;
		}
		return 0;

	}
	GLint OpenGLEnum(TextureFilter format)
	{
		switch (format)
		{
		case NEAREST: return GL_NEAREST;
		case LINEAR:  return GL_LINEAR;
		}
		return 0;
	}
	GLint OpenGLEnum(TextureWrap format)
	{
		switch (format)
		{
		case REPEAT:return GL_REPEAT;
		case MIRRORED_REPEAT:return GL_MIRRORED_REPEAT;
		case CLAMP_TO_EDGE:return GL_CLAMP_TO_EDGE;
		}
		return 0;
	}
	GLint GetDateInternalFormat(TextureInternalFormat format)
	{
		switch (format)
		{
		case RGB4:	 
		case RGB5:	 
		case RGB8:	 
		case RGB10:	 
		case RGB12:	 
		case RGB16:	 
		case RGBA2:	 
		case RGBA4:	 
		case RGB5A1: 
		case RGBA8:	 
		case RGB10A2:
		case RGBA12: 
		case RGBA16: return GL_UNSIGNED_BYTE;
		case RGBA32F:
		case RGB32F: 
		case RGBA16F:
		case RGB16F: return GL_FLOAT;
		}
		return 0;
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const ColorAttachmentSpecification& spec)
		:m_HasRBO(false),  m_ColorAttachmentSpec(spec)
	{
		Init();
	}
	OpenGLFrameBuffer::OpenGLFrameBuffer(const ColorAttachmentSpecification& cas, const RenderBufferSpecification& rbs)
		:m_HasRBO(true), m_ColorAttachmentSpec(cas), m_RenderBufferSpec(rbs)
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
		glTexImage2D(GL_TEXTURE_2D, 0, OpenGLEnum(m_ColorAttachmentSpec.InternalFormat),
			m_ColorAttachmentSpec.Width, m_ColorAttachmentSpec.Height,
			0, OpenGLEnum(m_ColorAttachmentSpec.Format), GetDateInternalFormat(m_ColorAttachmentSpec.InternalFormat), nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OpenGLEnum(m_ColorAttachmentSpec.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OpenGLEnum(m_ColorAttachmentSpec.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OpenGLEnum(m_ColorAttachmentSpec.Wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OpenGLEnum(m_ColorAttachmentSpec.Wrap));

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		if (m_HasRBO)
		{
			unsigned int rbo;
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_RenderBufferSpec.Width, m_RenderBufferSpec.Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		}
		


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




	

	OpenGLMRTFrameBuffer::OpenGLMRTFrameBuffer(const ColorAttachmentSpecification* cas, unsigned amount, const RenderBufferSpecification* rbs)
		:m_Amount(amount)
	{
		for (int i = 0; i < m_Amount; i++)
		{
			auto spec = cas[i];
			m_ColorAttachmentSpec.push_back(spec);
		}
		if (rbs)
		{
			m_HasRBO = true;
			m_RenderBufferSpec = *rbs;
		}
		else
		{
			m_HasRBO = false;
		}
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

			glTexImage2D(GL_TEXTURE_2D, 0, OpenGLEnum(m_ColorAttachmentSpec[i].InternalFormat),
				m_ColorAttachmentSpec[i].Width, m_ColorAttachmentSpec[i].Height,
				0, OpenGLEnum(m_ColorAttachmentSpec[i].Format), GetDateInternalFormat(m_ColorAttachmentSpec[i].InternalFormat), nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OpenGLEnum(m_ColorAttachmentSpec[i].Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OpenGLEnum(m_ColorAttachmentSpec[i].Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OpenGLEnum(m_ColorAttachmentSpec[i].Wrap));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OpenGLEnum(m_ColorAttachmentSpec[i].Wrap));

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachment[i], 0);
			m_ColorAttachments.push_back(colorAttachment[i]);
		}
		unsigned int attachments[32];
		for (int i = 0; i < m_Amount; i++)
		{
			attachments[i] = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(m_Amount, attachments);
		if (m_HasRBO)
		{
			unsigned int rbo;
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_RenderBufferSpec.Width, m_RenderBufferSpec.Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		}

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