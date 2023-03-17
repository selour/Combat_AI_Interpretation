#include "stdafx.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
namespace Engine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
        
        // 加载图片
        int width, height, nrComponents;
        stbi_set_flip_vertically_on_load(1);

        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        ENGINE_ASSERT(image, "Failed to load image!");

        m_Width = width;
        m_Height = height;


     
        internalFormat = 0, dataFormat = 0;
        if (nrComponents == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } 
        else if (nrComponents == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 1)
        {
            internalFormat = GL_RED;
            dataFormat = GL_RED;
        }
            
        ENGINE_ASSERT(internalFormat & dataFormat, "Format not supported!");
      

        //创建纹理
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);
        //设置纹理
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, image);
       
        // 释放图像数据空间
        stbi_image_free(image);
        
	}
    OpenGLTexture2D::OpenGLTexture2D()
        :m_Width(1), m_Height(1)
    {

        internalFormat = GL_RGBA8, dataFormat = GL_RGBA;
        
        //创建纹理
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);
        //设置纹理
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);

        unsigned int WhiteData = 0xffffffff;
        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, &WhiteData);
    }
	OpenGLTexture2D::~OpenGLTexture2D()
	{
        glDeleteTextures(1, &m_TextureID); 
	}
    void OpenGLTexture2D::Bind(unsigned slot) const
	{
        glBindTextureUnit(slot, m_TextureID);
	}



    OpenGLTexture2DArray::OpenGLTexture2DArray(const std::string& path, unsigned int xIndex, unsigned int yIndex)
    {
        // 加载图片
        int width, height, nrComponents;
        stbi_set_flip_vertically_on_load(1);

        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        ENGINE_ASSERT(image, "Failed to load image!");
       
        m_Width = width / xIndex;
        m_Height = height / yIndex;
        m_Count = xIndex * yIndex;
       
  
        internalFormat = 0, dataFormat = 0;
        if (nrComponents == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (nrComponents == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 1)
        {
            internalFormat = GL_RED;
            dataFormat = GL_RED;
        }

        ENGINE_ASSERT(internalFormat & dataFormat, "Format not supported!");
        //创建纹理
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internalFormat, m_Width, m_Height, m_Count);
        //设置纹理
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        for (unsigned int y = 0; y < height; y++)
        {
            glTexSubImage3D(
                GL_TEXTURE_2D_ARRAY,
                0,
                0, y, (y / m_Height)*xIndex ,
                m_Width, 1, m_Count,
                dataFormat,
                GL_UNSIGNED_BYTE,
                (image  + y * width * nrComponents));
        }
        

        // 释放图像数据空间
        stbi_image_free(image);
    }
    OpenGLTexture2DArray::OpenGLTexture2DArray()
        :m_Width(1), m_Height(1), m_Count(1)
    {
        internalFormat = GL_RGBA8, dataFormat = GL_RGBA;
        //创建纹理
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internalFormat, m_Width, m_Height, m_Count);
        //设置纹理
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT); 
       
        unsigned int WhiteData = 0xffffffff;
        glTexSubImage3D(
                    GL_TEXTURE_2D_ARRAY,
                    0,
                    0, 0, 0,
                    1, 1, 1,
                    dataFormat,
                    GL_UNSIGNED_BYTE,
                    &WhiteData);

    }
    OpenGLTexture2DArray::~OpenGLTexture2DArray()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLTexture2DArray::Bind(unsigned slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID);
    }
}