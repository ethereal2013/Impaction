#pragma once

#include <memory>

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

#else
	#error Impaction only supports Windows
#endif

#ifdef IMPCT_DEBUG
	#define IMPCT_ENABLE_ASSERTS
#endif

#ifdef IMPCT_ENABLE_ASSERTS
	#define IMPCT_ASSERT(x, ...) { if(!(x)) { IMPCT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }	
	#define IMPCT_CORE_ASSERT(x, ...) { if(!(x)) { IMPCT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
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
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using IPSharedPtr = Ref<T>;

	template<typename T>
	using IPUniquePtr = Scope<T>;

}
