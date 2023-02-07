#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
namespace Engine
{

	class SubTexture2D
	{
	public:
		SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
	
		const std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoord() const { return m_TexCoord; }

		static std::shared_ptr<SubTexture2D> CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize);
	
	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec2 m_TexCoord[4];
	};


}

