#include <impct_pch.h>

#include "ImGuiLayer.h"
#include <imgui.h>

#include "Impaction/Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Impaction/Application.h"
#include "KeyCode.h"

namespace impct
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
	ImGuiLayer::~ImGuiLayer() {}


	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");

		// TODO: Add modern ImGui keyboard input handling, and
		// using io.AddKeyEvent() when GLFW input is connected.
	}

	void ImGuiLayer::OnDetach() {}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(
			static_cast<float>(app.GetWindow().GetWidth()), 
			static_cast<float>(app.GetWindow().GetHeight())
		);

		float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent)
		);

		dispatcher.Dispatch<MouseButtonReleasedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent)
		);

		dispatcher.Dispatch<MouseScrolledEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent)
		);

		dispatcher.Dispatch<MouseMovedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent)
		);

		dispatcher.Dispatch<KeyPressedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent)
		);

		dispatcher.Dispatch<KeyReleasedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent)
		);

		dispatcher.Dispatch<KeyTypedEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent)
		);

		dispatcher.Dispatch<WindowResizeEvent>(
			IMPCT_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent)
		);
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddMouseWheelEvent(
			static_cast<float>(e.GetXOffset()),
			static_cast<float>(e.GetYOffset())
		);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddMousePosEvent(
			static_cast<float>(e.GetX()),
			static_cast<float>(e.GetY())
		);

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		const ImGuiKey key = GLFWToImGui(e.GetKeyCode());
		if (key != ImGuiKey_None) io.AddKeyEvent(key, true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		const ImGuiKey key = GLFWToImGui(e.GetKeyCode());
		if (key != ImGuiKey_None) io.AddKeyEvent(key, false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x1000) io.AddInputCharacter(
			static_cast<unsigned short>(keycode)
		);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(
			static_cast<float>(e.GetWidth()),
			static_cast<float>(e.GetHeight())
		);

		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); //Will do later
		glViewport(0, 0, e.GetWidth(), e.GetHeight());


		return false;
	}
}
