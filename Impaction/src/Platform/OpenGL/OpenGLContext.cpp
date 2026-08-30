#include "impct_pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace impct
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		IMPCT_CORE_ASSERT(m_windowHandle, "Window Handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);

		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		IMPCT_CORE_ASSERT(status, "Failed to initialize Glad!");

		IMPCT_CORE_INFO("\nOpenGL Info:\n");
		IMPCT_CORE_INFO("   Vendor: {0}",   reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		IMPCT_CORE_INFO("   Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		IMPCT_CORE_INFO("   Version: {0}\n",  reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}