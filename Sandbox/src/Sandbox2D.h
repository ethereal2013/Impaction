#pragma once

#include <Impaction.h>

class Sandbox2D : public impct::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() noexcept = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(impct::Timestep ts) override;
	virtual void OnEvent(impct::Event& e) override;
	virtual void OnImGuiRender() override;

private:
	impct::OrthographicCameraController m_CameraController;
	
	//TEMPORARY
	impct::Ref<impct::VertexArray> m_SquareVA;
	impct::Ref<impct::Shader> m_FlatColorShader;

	impct::Ref<impct::Texture2D> m_ChessTexture;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};