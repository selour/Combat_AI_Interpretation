#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

//核心日志宏
#define ENGINE_CORE_FATAL(...)	::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)	::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)	::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)	::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...)	::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
//客户日志宏
#define ENGINE_FATAL(...)		::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define ENGINE_ERROR(...)		::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_WARN(...)		::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_INFO(...)		::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_TRACE(...)		::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
namespace Engine
{

	class Log
	{
	public:
		// 初始化日志系统
		static void Init();
		// 存储核心日志
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		// 存储客户日志
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


