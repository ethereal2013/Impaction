#pragma once

#include "Core.h"
#include "Window.h"

#include "Impaction/LayerStack.h"

#include "Impaction/Events/Event.h"
#include "Impaction/Events/ApplicationEvent.h"

#include "Impaction/ImGui/ImGuiLayer.h"

#include "Impaction/Renderer/Shader.h"
#include "Impaction/Renderer/Buffer.h"
#include "Impaction/Renderer/VertexArray.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
		
	private:
		static Application* s_Instance;
	};

	//To be definded in Client.
	[[nodiscard]] Application* CreateApplication();
}