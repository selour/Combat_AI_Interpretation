#include "stdafx.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLShader.h"
#include "Engine/Core/Core.h"

namespace Engine
{
    static GLenum StringToShaderType(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;
        ENGINE_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        :m_Name(name)
    {

        GLuint sVertex, sFragment;
        // Vertex Shader
        sVertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = (const GLchar*)vertexSrc.c_str();
        glShaderSource(sVertex, 1, &source, NULL);
        glCompileShader(sVertex);

        checkCompileErrors(sVertex, GL_VERTEX_SHADER);
        // Fragment Shader
        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        source = (const GLchar*)fragmentSrc.c_str();
        glShaderSource(sFragment, 1, &source, NULL);
        glCompileShader(sFragment);
        checkCompileErrors(sFragment, GL_FRAGMENT_SHADER);

        // Shader Program
        this->m_ShaderID = glCreateProgram();
        glAttachShader(this->m_ShaderID, sVertex);
        glAttachShader(this->m_ShaderID, sFragment);

        glLinkProgram(this->m_ShaderID);
        checkCompileErrors(this->m_ShaderID, 0);
        // Delete
        glDeleteShader(sVertex);
        glDeleteShader(sFragment);

    }
    OpenGLShader::OpenGLShader(const std::string& filePath)
    {
        std::string src = ReadFile(filePath);
        auto shaderSrc = PreProcess(src);
        Compile(shaderSrc);
        //获取文件名
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filePath.substr(lastSlash, count);


    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderID);
    }
    void OpenGLShader::Use() const
    {
        glUseProgram(m_ShaderID);
    }
    void OpenGLShader::UnUse() const
    {
        glUseProgram(0);
    }



    void OpenGLShader::SetFloat(const char* name, float value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1f(glGetUniformLocation(this->m_ShaderID, name), value);
    }
    void OpenGLShader::SetInteger(const char* name, int value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1i(glGetUniformLocation(this->m_ShaderID, name), value);
    }
    void OpenGLShader::SetIntegerArray(const char* name, int* values, unsigned int count, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1iv(glGetUniformLocation(this->m_ShaderID, name), count, values);
    }

    void OpenGLShader::SetVector2f(const char* name, float x, float y, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->m_ShaderID, name), x, y);
    }
    void OpenGLShader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y);
    }
    void OpenGLShader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->m_ShaderID, name), x, y, z);
    }
    void OpenGLShader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z);
    }
    void OpenGLShader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->m_ShaderID, name), x, y, z, w);
    }
    void OpenGLShader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z, value.w);
    }
    void OpenGLShader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }



    std::string OpenGLShader::ReadFile(const std::string& filePath)
    {
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            ENGINE_CORE_ERROR("Could not open file '{0}'", filePath);
        }
        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
    {
        std::unordered_map<GLenum, std::string> shaderSrc;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = src.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = src.find_first_of("\r\n", pos);
            ENGINE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = src.substr(begin, eol - begin);
            ENGINE_CORE_ASSERT(StringToShaderType(type), "Invalid shader type specified!");

            size_t nextLinePos = src.find_first_not_of("\r\n", eol);
            pos = src.find(typeToken, nextLinePos);
            shaderSrc[StringToShaderType(type)] = src.substr(nextLinePos,
                pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
        }
        return shaderSrc;
    }

    void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSrc)
    {
        this->m_ShaderID = glCreateProgram();
        ENGINE_CORE_ASSERT(shaderSrc.size() <= 2, "Too many shaders!");
        std::array<GLenum, 2> ShaderIDs;
        int ShaderIDIndex = 0;
        for (auto& kv : shaderSrc)
        {
            GLenum type = kv.first;
            const std::string& src = kv.second;
            GLuint shader = glCreateShader(type);
            const GLchar* source = (const GLchar*)src.c_str();
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            checkCompileErrors(shader, type);
            glAttachShader(this->m_ShaderID, shader);
            ShaderIDs[ShaderIDIndex++] = shader;
        }

        glLinkProgram(this->m_ShaderID);
        checkCompileErrors(this->m_ShaderID, 0);
        // Delete
        for (auto id : ShaderIDs)
        {
            glDeleteShader(id);
        }
     
    }

    void OpenGLShader::checkCompileErrors(GLuint object, GLenum type)
    {
        GLint success;
        GLchar infoLog[1024];
        std::stringstream ss;
        if (!type)
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                if (type == GL_VERTEX_SHADER)
                {
                    glGetShaderInfoLog(object, 1024, NULL, infoLog);
                    ss << "| ERROR::SHADER: Compile-time error: Type: VertexShader\n"
                        << infoLog << "\n -- --------------------------------------------------- -- "
                        << std::endl;
                    ENGINE_CORE_ERROR(ss.str());
                    ENGINE_CORE_ASSERT(false, "Shader Compilation failure!")
                }
                else if (type == GL_FRAGMENT_SHADER)
                {
                    glGetShaderInfoLog(object, 1024, NULL, infoLog);
                    ss << "| ERROR::SHADER: Compile-time error: Type: FragmentShader\n"
                        << infoLog << "\n -- --------------------------------------------------- -- "
                        << std::endl;
                    ENGINE_CORE_ERROR(ss.str());
                    ENGINE_CORE_ASSERT(false, "Shader Compilation failure!")
                }
                

            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                ss << "| ERROR::Shader: Link-time error: Type: Program\n"
                    << infoLog << "\n -- --------------------------------------------------- -- "
                    << std::endl;
                ENGINE_CORE_ERROR(ss.str());
                ENGINE_CORE_ASSERT(false, "Shader Link failure!")
            }
        }
    }
}