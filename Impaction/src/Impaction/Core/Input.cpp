#include "impct_pch.h"
#include "Input.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/Linux/LinuxInput.h"

namespace impct
{
    Input* Input::Create()
    {
#ifdef IMPCT_PLATFORM_WINDOWS
        return new WindowsInput();
#elif defined(IMPCT_PLATFORM_LINUX)
        return new LinuxInput();
#else
        IMPCT_CORE_ASSERT(false, "Platform not supported")
#endif
    }
}
