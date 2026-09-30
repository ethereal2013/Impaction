#pragma once

#include <Impaction.h>

class Sandbox2D : public impct::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() noexcept override = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(impct::Timestep ts) override;
	void OnEvent(impct::Event& e) override;
	void OnImGuiRender() override;

private:
	impct::OrthographicCameraController m_CameraController;

	impct::Ref<impct::Texture2D> m_ChessTexture;
	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};