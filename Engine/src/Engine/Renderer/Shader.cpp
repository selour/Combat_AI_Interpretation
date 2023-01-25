#include "stdafx.h"
#include "Shader.h"
#include <glad/glad.h>
namespace Engine
{
	Shader::Shader(const std::string& vertexSrc, const std::string fragmentSrc)
	{

        GLuint sVertex, sFragment, gShader;
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