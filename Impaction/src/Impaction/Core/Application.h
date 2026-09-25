#pragma once

#include "Impaction/Core/Core.h"
#include "Impaction/Core/Window.h"
#include "Impaction/Core/Input.h"

#include "Impaction/Core/LayerStack.h"

#include "Impaction/Events/Event.h"
#include "Impaction/Events/ApplicationEvent.h"

#include "Impaction/ImGui/ImGuiLayer.h"

#include "Impaction/Core/Timestep.h"

namespace impct 
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;
		
	private:
		static Application* s_Instance;
	};

	//To be defined in Client.
	[[nodiscard]] Application* CreateApplication();
}