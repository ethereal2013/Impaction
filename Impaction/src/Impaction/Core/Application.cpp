#include "impct_pch.h"
#include "Application.h"

#include "Impaction/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace impct
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		IMPCT_PROFILE_FUNCTION();

		IMPCT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(IMPCT_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(true); //60 FPS

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() { IMPCT_PROFILE_FUNCTION(); Renderer::Shutdown(); }

	void Application::PushLayer(Layer* layer) 
	{
		IMPCT_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) 
	{
		IMPCT_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) 
	{
		IMPCT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(IMPCT_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(IMPCT_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}

	void Application::Run() 
	{
		IMPCT_PROFILE_FUNCTION();

		while (m_Running)
		{
			IMPCT_PROFILE_SCOPE("Run Loop");

			float time = static_cast<float>(glfwGetTime()); // XPlatform::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				IMPCT_PROFILE_SCOPE("Layerstack OnUpdate");
				for (Layer* layer : m_LayerStack) layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			{
				IMPCT_PROFILE_SCOPE("Layerstack OnImGuiRender");

				for (Layer* layer : m_LayerStack) layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) 
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		IMPCT_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}
