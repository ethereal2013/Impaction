#include "impct_pch.h"
#include "LinuxWindow.h"
#include "Impaction/Core/Core.h"

#include "Impaction/Events/KeyEvent.h"
#include "Impaction/Events/MouseEvent.h"
#include "Impaction/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace impct
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		IMPCT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	LinuxWindow::LinuxWindow(const WindowProps& props) 
	{
		IMPCT_PROFILE_FUNCTION();
		LinuxWindow::Init(props);
	}

	LinuxWindow::~LinuxWindow() 
	{
		IMPCT_PROFILE_FUNCTION();
		LinuxWindow::Shutdown();
	}

	void LinuxWindow::Init(const WindowProps& props)
	{
		IMPCT_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		IMPCT_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// GLFW Terminate on system shutdown.
			IMPCT_PROFILE_SCOPE("glfwInit");

			int success = glfwInit();
			IMPCT_CORE_ASSERT(success, "Could not initialize GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		{
			IMPCT_PROFILE_SCOPE("glfwCreateWindow");

			m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height),
				m_Data.Title.c_str(), nullptr, nullptr);
		}

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height)
		{

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			data.Width = static_cast<unsigned int>(width);
			data.Height = static_cast<unsigned int>(height);

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;

			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, const int key, int scancode, const int action, int mods)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, const unsigned int keycode)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(static_cast<int>(keycode));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, const int button, const int action, int mods)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const double xOffset, const double yOffset)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));

			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const double xPos, const double yPos)
		{
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));

			data.EventCallback(event);
		});

	}

	void LinuxWindow::Shutdown() 
	{
		IMPCT_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
	}

	void LinuxWindow::OnUpdate()
	{
		IMPCT_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void LinuxWindow::SetVSync(const bool enabled)
	{
		IMPCT_PROFILE_FUNCTION();

		if (enabled) glfwSwapInterval(1); 
		else glfwSwapInterval(0);
		m_Data.Vsync = enabled;
	}

	bool LinuxWindow::IsVSync() const { return m_Data.Vsync; }

}
