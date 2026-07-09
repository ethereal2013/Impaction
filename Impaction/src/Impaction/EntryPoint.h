#pragma once

#ifdef IMPCT_PLATFORM_WINDOWS
	
extern impct::Application* impct::CreateApplication();

int main(int argc, char** argv) {

	auto app = impct::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif