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
	m_ChessTexture = impct::Texture2D::Create("assets/textures/chess.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(impct::Timestep ts)
{
	IMPCT_PROFILE_FUNCTION();

	{
		IMPCT_PROFILE_SCOPE("CameraController.OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		IMPCT_PROFILE_SCOPE("Renderer Start");
		impct::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		impct::RenderCommand::Clear();
	}

	{
		IMPCT_PROFILE_SCOPE("Renderer Draw");
		impct::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			impct::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 0.0f, m_SquareColor);
			impct::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, 0.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
			impct::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 50.0f, 50.0f }, 0.0f, m_ChessTexture);
		}
		impct::Renderer2D::EndScene();
	}
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
