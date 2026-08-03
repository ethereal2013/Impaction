#pragma once
#include "Core.h"

namespace impct 
{
	class IMPCT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be definded in Client.
	Application* CreateApplication();

}