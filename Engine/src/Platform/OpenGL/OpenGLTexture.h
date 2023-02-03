#pragma once
#include <glad/glad.h>
#include "Engine/Renderer/Texture.h"

namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned slot = 0) const override;
	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int m_TextureID;
		GLenum internalFormat, dataFormat;
	};

}

