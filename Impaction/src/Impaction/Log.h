#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace impct 
{

	class IMPCT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core Log Macros
#define IMPCT_CORE_TRACE(...)    ::impct::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IMPCT_CORE_INFO(...)     ::impct::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IMPCT_CORE_WARN(...)     ::impct::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IMPCT_CORE_ERROR(...)    ::impct::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IMPCT_CORE_CRITICAL(...) ::impct::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Client Log  Macros
#define IMPCT_TRACE(...)         ::impct::Log::GetClientLogger()->trace(__VA_ARGS__)
#define IMPCT_INFO(...)          ::impct::Log::GetClientLogger()->info(__VA_ARGS__)
#define IMPCT_WARN(...)          ::impct::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IMPCT_ERROR(...)         ::impct::Log::GetClientLogger()->error(__VA_ARGS__)
#define IMPCT_CRITICAL(...)      ::impct::Log::GetClientLogger()->critical(__VA_ARGS__)
