#pragma once

#ifdef IMPCT_PLATFORM_WINDOWS
	
extern impct::Application* impct::CreateApplication();

int main(int argc, char** argv)
{
	impct::Log::Init();

	IMPCT_PROFILE_BEGIN_SESSION("Startup", "ImpactionProfile-Startup.json");
	auto app = impct::CreateApplication();
	IMPCT_PROFILE_END_SESSION();

	IMPCT_PROFILE_BEGIN_SESSION("Runtime", "ImpactionProfile-Runtime.json");
	app->Run();
	IMPCT_PROFILE_END_SESSION();

	IMPCT_PROFILE_BEGIN_SESSION("Shutdown", "ImpactionProfile-Shutdown.json");
	delete app;
	IMPCT_PROFILE_END_SESSION();

	return 0;
}

#endif