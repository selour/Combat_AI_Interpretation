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
    class Texture2DArrayLibrary
    {
    public:
        void Add(const std::shared_ptr<Texture2DArray>& texture, const std::string& name);
        std::shared_ptr<Texture2DArray> Load(const std::string& name, const std::string& filePath, unsigned int xIndex, unsigned int yIndex);
        std::shared_ptr<Texture2DArray> Get(const std::string& name);
        bool IsExists(const std::string& name) const;
    private:
        std::unordered_map<std::string, std::shared_ptr<Texture2DArray>> m_Textures;
    };

}


