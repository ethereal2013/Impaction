#pragma once

#ifdef IMPCT_PLATFORM_WINDOWS
	
extern impct::Application* impct::CreateApplication();

int main(int argc, char** argv) {

	impct::Log::Init();
	IMPCT_CORE_WARN("Initialized Impaction!\nNow Ready with Logging and Events");

	IMPCT_CORE_INFO("Today I Implemented Event System");

	auto app = impct::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif