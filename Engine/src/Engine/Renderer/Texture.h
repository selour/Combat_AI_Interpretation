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

        virtual void SetData(void* data, unsigned int size) = 0;

		virtual void Bind(unsigned slot = 0) const = 0;
	};
    //2D����
    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> Create(unsigned int width, unsigned int height);
        static std::shared_ptr<Texture2D> Create(const std::string& path);
    
    };


}


