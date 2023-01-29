#include "stdafx.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
namespace Engine
{
	Shader::Shader(const std::string& vertexSrc, const std::string fragmentSrc)
	{

        GLuint sVertex, sFragment;
        // Vertex Shader
        sVertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = (const GLchar*)vertexSrc.c_str();
        glShaderSource(sVertex, 1, &source, NULL);
        glCompileShader(sVertex);

        checkCompileErrors(sVertex, "VERTEX");
        // Fragment Shader
        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        source = (const GLchar*)fragmentSrc.c_str();
        glShaderSource(sFragment, 1, &source, NULL);
        glCompileShader(sFragment);
        checkCompileErrors(sFragment, "FRAGMENT");
        
        // Shader Program
        this->m_ShaderID = glCreateProgram();
        glAttachShader(this->m_ShaderID, sVertex);
        glAttachShader(this->m_ShaderID, sFragment);
      
        glLinkProgram(this->m_ShaderID);
        checkCompileErrors(this->m_ShaderID, "PROGRAM");
        // Delete
        glDeleteShader(sVertex);
        glDeleteShader(sFragment);
       
	}
	Shader::~Shader()
	{
        glDeleteProgram(m_ShaderID);
	}
	void Shader::Use() const
	{
        glUseProgram(m_ShaderID);
	}
	void Shader::UnUse() const
	{
        glUseProgram(0);
	}



    void Shader::SetFloat(const char* name, float value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1f(glGetUniformLocation(this->m_ShaderID, name), value);
    }
    void Shader::SetInteger(const char* name, int value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1i(glGetUniformLocation(this->m_ShaderID, name), value);
    }
    void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->m_ShaderID, name), x, y);
    }
    void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y);
    }
    void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->m_ShaderID, name), x, y, z);
    }
    void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z);
    }
    void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->m_ShaderID, name), x, y, z, w);
    }
    void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z, value.w);
    }
    void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }



    void Shader::checkCompileErrors(GLuint object, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        std::stringstream ss;
        if (type != "PROGRAM")
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, 1024, NULL, infoLog);
                ss << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- "
                    << std::endl;
                ENGINE_CORE_ERROR(ss.str());
                ENGINE_CORE_ASSERT(false, "Shader Compilation failure!")
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                ss << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- "
                    << std::endl;
                ENGINE_CORE_ERROR(ss.str());
                ENGINE_CORE_ASSERT(false, "Shader Link failure!")
            }
        }
    }
}