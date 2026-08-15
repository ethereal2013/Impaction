#pragma once

#include "Core.h"
#include "Window.h"

#include "Impaction/LayerStack.h"

#include "Impaction/Events/Event.h"
#include "Impaction/Events/ApplicationEvent.h"

#include "Impaction/ImGui/ImGuiLayer.h"


namespace impct 
{

	class IMPCT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	//To be definded in Client.
	Application* CreateApplication();
}