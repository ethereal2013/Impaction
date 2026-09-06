#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(impct::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	m_CameraController.OnUpdate(ts);

	impct::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	impct::RenderCommand::Clear();

	impct::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		impct::Renderer2D::DrawQuad( { 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor );
	}
	impct::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(impct::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	{
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
	}
	ImGui::End();
}
