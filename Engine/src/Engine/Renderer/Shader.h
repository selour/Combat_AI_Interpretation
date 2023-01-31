#pragma once
#include <string>
#include <memory>
#include <unordered_map>
namespace Engine
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Use() const = 0;
		virtual void UnUse() const = 0;
		virtual const std::string& GetName() const = 0;
		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string fragmentSrc);
		static std::shared_ptr<Shader> Create(const std::string& filePath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader, const std::string& name);
		std::shared_ptr<Shader> Load(const std::string& filePath);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& filePath);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string fragmentSrc);
		std::shared_ptr<Shader> Get(const std::string& name);
		bool IsExists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}