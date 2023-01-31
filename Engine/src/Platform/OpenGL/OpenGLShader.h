#pragma once
#include <string>
#include <glm/glm.hpp>

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

		// uniform���ߺ���
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
		std::string m_Name;
		//������ɫ���ļ�
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSrc);

		// �����ɫ�������Ƿ����
		void checkCompileErrors(GLuint object, GLenum type);
	};

}