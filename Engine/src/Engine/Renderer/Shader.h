#pragma once
#include <string>
#include <glm/glm.hpp>
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

		// uniform工具函数
		void SetFloat(const char* name, float value, bool useShader = false);
		void SetInteger(const char* name, int value, bool useShader = false);
		void SetVector2f(const char* name, float x, float y, bool useShader = false);
		void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
		void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
		void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
		void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
		void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
		void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

	private:
		unsigned int m_ShaderID;
	private:
		// 检查着色器构造是否出错
		void checkCompileErrors(GLuint object, std::string type);
	};

}