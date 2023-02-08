#pragma once
#include <memory>
namespace Engine
{

	class Texture
	{
	public:
        virtual ~Texture() {};

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
        virtual unsigned int GetCount() const = 0;
        //virtual void SetData(void* data, unsigned int size) = 0;

		virtual void Bind(unsigned slot = 0) const = 0;

       
	};
    //2D纹理
    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> Create();
        static std::shared_ptr<Texture2D> Create(const std::string& path);

       
    
    };
    //2D纹理数组
    class Texture2DArray : public Texture
    {
    public:
        static std::shared_ptr<Texture2DArray> Create();
        static std::shared_ptr<Texture2DArray> Create(const std::string& path, unsigned int xIndex, unsigned int yIndex);


    };

}


