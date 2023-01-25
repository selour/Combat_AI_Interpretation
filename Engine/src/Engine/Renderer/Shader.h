#pragma once
#include <string>
typedef unsigned int GLuint;
namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string fragmentSrc);
		~Shader();

		void Use() const;
		void UnUse() const;
	private:
		unsigned int m_ShaderID;
	private:
		// �����ɫ�������Ƿ����
		void checkCompileErrors(GLuint object, std::string type);
	};

}