#pragma once
namespace Engine
{
	class PlatformAPI
	{
	public:
		enum class API
		{
			None = 0,
			GLFW = 1

		};
		virtual float GetTime() = 0;
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}

