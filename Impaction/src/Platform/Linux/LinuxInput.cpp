#include "impct_pch.h"
#include "LinuxInput.h"

#include <GLFW/glfw3.h>
#include "Impaction/Core/Application.h"

namespace impct
{
    Input* Input::s_Instance = Input::Create();

    bool LinuxInput::IsKeyPressedImpl(const int keycode)
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(const int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePosImpl()
    {
        double xpos, ypos;

        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        glfwGetCursorPos(window, &xpos, &ypos);

        return { static_cast<float>(xpos), static_cast<float>(ypos) };
    }

    float LinuxInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return x;
    }

    float LinuxInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }

}
