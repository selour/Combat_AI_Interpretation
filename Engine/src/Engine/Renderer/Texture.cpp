#include "stdafx.h"
#include "Texture.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Engine
{
	//------------------------2D纹理--------------------------
	std::shared_ptr<Texture2D> Texture2D::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>();
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	//------------------------2D纹理数组--------------------------
	std::shared_ptr<Texture2DArray> Texture2DArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2DArray>();
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Texture2DArray> Texture2DArray::Create(const std::string& path, unsigned int xIndex, unsigned int yIndex)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2DArray>(path, xIndex, yIndex);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	//------------------------2D纹理数组库--------------------------

	void Texture2DArrayLibrary::Add(const std::shared_ptr<Texture2DArray>& texture, const std::string& name)
	{
		ENGINE_CORE_ASSERT(!IsExists(name), "Texture already exists!");
		m_Textures[name] = texture;
	}


	std::shared_ptr<Texture2DArray> Texture2DArrayLibrary::Load(const std::string& name, const std::string& filePath, unsigned int xIndex, unsigned int yIndex)
	{
		auto texture = Texture2DArray::Create(filePath, xIndex, yIndex);
		Add(texture,name);
		return texture;
	}

	std::shared_ptr<Texture2DArray> Texture2DArrayLibrary::Get(const std::string& name)
	{
		ENGINE_CORE_ASSERT(IsExists(name), "Texture not found!");
		return m_Textures[name];
	}

	bool Texture2DArrayLibrary::IsExists(const std::string& name) const
	{
		return m_Textures.find(name) != m_Textures.end() && !m_Textures.empty();
	}

}
