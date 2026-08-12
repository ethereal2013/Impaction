#include <Impaction.h>

class ExampleLayer : public impct::Layer
{
public:
	ExampleLayer() :Layer("Example") { }

	void OnUpdate() override { IMPCT_INFO("ExampleLayer::Update"); }
	void OnEvent(impct::Event& event) override { IMPCT_TRACE("{0}", event); }
};

class Sandbox : public impct::Application
{
public:
	Sandbox() { 
		PushLayer(new ExampleLayer()); 
		PushOverlay(new impct::ImGuiLayer());
	}
	~Sandbox() override {}
};

impct::Application* impct::CreateApplication() {
	return new Sandbox();
}