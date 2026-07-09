#include <Impaction.h>

class Sandbox : public impct::Application {
public:
	Sandbox() {}
	~Sandbox() override {}
};

impct::Application* impct::CreateApplication() {
	return new Sandbox();
}