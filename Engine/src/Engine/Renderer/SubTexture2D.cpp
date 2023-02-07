#include "stdafx.h"
#include "SubTexture2D.h"

namespace Engine
{
	SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:m_Texture(texture)
	{
		
		m_TexCoord[0] = { min.x, min.y };
		m_TexCoord[1] = { max.x, min.y };
		m_TexCoord[2] = { max.x, max.y };
		m_TexCoord[3] = { min.x, max.y };
	}
	std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		
		glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight() };
		return std::make_shared<SubTexture2D>(texture, min, max);
	}
}