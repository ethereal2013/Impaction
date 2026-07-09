#pragma once

#ifdef IMPCT_PLATFORM_WINDOWS
	#ifdef IMPCT_BUILD_DLL
		#define IMPCT_API __declspec(dllexport)
	#else
		#define IMPCT_API __declspec(dllimport)
	#endif

#else
	#error Impaction only supports Windows

#endif