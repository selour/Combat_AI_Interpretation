#pragma once
#include <glad/glad.h>
#include "Engine/Renderer/Texture.h"

namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D();
		virtual ~OpenGLTexture2D() override;

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
		virtual unsigned int GetCount() const override { return 1; }


		virtual void Bind(unsigned slot = 0) const override;
	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int m_TextureID;
		GLenum internalFormat, dataFormat;
	};


	class OpenGLTexture2DArray : public Texture2DArray
	{
	public:
		OpenGLTexture2DArray(const std::string& path, unsigned int xIndex, unsigned int yIndex);
		OpenGLTexture2DArray();
		virtual ~OpenGLTexture2DArray() override;

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
		virtual unsigned int GetCount() const override { return m_Count; }


		virtual void Bind(unsigned slot = 0) const override;
	private:
		std::string m_Path;
		unsigned int m_Width, m_Height, m_Count;
		unsigned int m_TextureID;
		GLenum internalFormat, dataFormat;
	};

}

