#pragma once
#include <string>

namespace Engine
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Use() const = 0;
		virtual void UnUse() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string fragmentSrc);

	};

}