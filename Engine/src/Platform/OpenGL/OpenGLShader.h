#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Engine/Renderer/Shader.h"
typedef unsigned int GLuint;

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Use() const override;
		virtual void UnUse() const override;

		// uniform工具函数
		void SetFloat(const char* name, float value, bool useShader);
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