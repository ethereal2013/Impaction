#pragma once

#include "Core.h"
#include "Window.h"

namespace impct 
{

	class IMPCT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be definded in Client.
	Application* CreateApplication();

}