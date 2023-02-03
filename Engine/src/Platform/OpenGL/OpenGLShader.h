#pragma once
#include <string>
#include "Engine/Renderer/Shader.h"
typedef unsigned int GLuint;
typedef unsigned int GLenum;
namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string fragmentSrc);
		OpenGLShader(const std::string& filePath);
		virtual ~OpenGLShader() override;

		virtual void Use() const override;
		virtual void UnUse() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		// uniform工具函数
		virtual void SetFloat(const char* name, float value, bool useShader) override;
		virtual void SetInteger(const char* name, int value, bool useShader = false) override;
		virtual void SetVector2f(const char* name, float x, float y, bool useShader = false) override;
		virtual void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false) override;
		virtual void SetVector3f(const char* name, float x, float y, float z, bool useShader = false) override;
		virtual void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false) override;
		virtual void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false) override;
		virtual void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false) override;
		virtual void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false) override;

	private:
		unsigned int m_ShaderID;
		std::string m_Name;
		//解析着色器文件
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSrc);

		// 检查着色器构造是否出错
		void checkCompileErrors(GLuint object, GLenum type);
	};

}