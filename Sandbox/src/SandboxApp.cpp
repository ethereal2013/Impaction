#include <Impaction.h>
#include <imgui/imgui.h>

class ExampleLayer : public impct::Layer
{
public:
	ExampleLayer() :Layer("Example") { }

	void OnUpdate() override
	{
		IMPCT_INFO("ExampleLayer::Update");
	}

	void OnEvent(impct::Event& event) override
	{
		IMPCT_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}
};

class Sandbox : public impct::Application
{
public:
	Sandbox()
	{ 
		PushLayer(new ExampleLayer()); 
	}

	~Sandbox() override {}
};

impct::Application* impct::CreateApplication()
{
	return new Sandbox();
}