#pragma once

#include <memory>
#include <utility>

// Platform detection using predefined macros
#ifdef _WIN32

	#ifdef _WIN64
		#define IMPCT_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif

#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define IMPCT_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define IMPCT_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

#elif defined(__ANDROID__)
	#define IMPCT_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define IMPCT_PLATFORM_LINUX
#else
	#error "Unknown platform!"

#endif

#ifdef IMPCT_PLATFORM_WINDOWS
	#if IMPCT_DYNAMIC_LINK
		#ifdef IMPCT_BUILD_DLL
			#define IMPCT_API __declspec(dllexport)
		#else
			#define IMPCT_API __declspec(dllimport)
		#endif
	#else
		#define IMPCT_API
	#endif

#elif defined(IMPCT_PLATFORM_LINUX)
	#if IMPCT_DYNAMIC_LINK
		#ifdef IMPCT_BUILD_DLL
			#define IMPCT_API __declspec(dllexport)
		#else
			#define IMPCT_API __declspec(dllimport)
		#endif
	#else
		#define IMPCT_API
	#endif

#else
	#error Impaction only supports Windows and Linux
#endif

#if defined(_MSC_VER)
	#define IMPCT_DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
	#define IMPCT_DEBUGBREAK() __builtin_trap()
#else
	#define IMPCT_DEBUGBREAK() std::abort()
#endif

#ifdef IMPCT_DEBUG
	#define IMPCT_ENABLE_ASSERTS
#endif

#ifdef IMPCT_ENABLE_ASSERTS
	#define IMPCT_ASSERT(x, ...) { if(!(x)) { IMPCT_ERROR("Assertion Failed: {0}", __VA_ARGS__); IMPCT_DEBUGBREAK(); } }	
	#define IMPCT_CORE_ASSERT(x, ...) { if(!(x)) { IMPCT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); IMPCT_DEBUGBREAK(); } }
#else
	#define IMPCT_ASSERT(x, ...)
	#define IMPCT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define IMPCT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace impct
{
	// Smart pointers

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using IPSharedPtr = Ref<T>;

	template <typename T, typename... Args>
	[[nodiscard]] constexpr Ref<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using IPUniquePtr = Scope<T>;

	template <typename T, typename... Args>
	[[nodiscard]] constexpr Scope<T> MakeScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
