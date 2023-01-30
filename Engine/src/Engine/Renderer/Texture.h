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

		virtual void Bind(unsigned slot = 0) const = 0;
	};
    //2DŒ∆¿Ì
    class Texture2D : public Texture
    {
    public:
       
        static Texture2D* Create(const std::string& path);
       
    };


}


