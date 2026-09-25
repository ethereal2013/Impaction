#include "impct_pch.h"

#include "Window.h"
#include "Impaction/Core/Core.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Linux/LinuxWindow.h"

namespace impct
{

    Scope<Window> Window::Create(const WindowProps &props)
    {
#ifdef IMPCT_PLATFORM_WINDOWS
        return MakeScope<WindowsWindow>(props);
#elif defined(IMPCT_PLATFORM_LINUX)
        return MakeScope<LinuxWindow>(props);
#else
    #error "Unsupported platform"
#endif
    }

}