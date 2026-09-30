#include "impct_pch.h"
#include "Impaction/Core/KeyCodes.h"
#include "Impaction/Core/Input.h"
#include "OrthographicCameraController.h"

#include <cmath>

namespace impct
{

	OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
		: m_AspectRatio(aspectRatio),
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		  m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(const Timestep ts)
	{
		IMPCT_PROFILE_FUNCTION();

		glm::vec2 cameraMovement(0.0f);

		if (Input::IsKeyPressed(IMPCT_KEY_A))	    cameraMovement.x -= 1.0f;
		else if (Input::IsKeyPressed(IMPCT_KEY_D))  cameraMovement.x += 1.0f;

		if (Input::IsKeyPressed(IMPCT_KEY_W))	    cameraMovement.y += 1.0f;
		else if (Input::IsKeyPressed(IMPCT_KEY_S))  cameraMovement.y -= 1.0f;

		if (m_Rotation)
		{
			const float cameraRotation = glm::radians(m_CameraRotation);

			cameraMovement = glm::vec2(
				cameraMovement.x * cos(cameraRotation) - cameraMovement.y * sin(cameraRotation),
				cameraMovement.x * sin(cameraRotation) + cameraMovement.y * cos(cameraRotation)
			);
		}

		m_CameraPosition.x += cameraMovement.x * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += cameraMovement.y * m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(IMPCT_KEY_Q)) m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(IMPCT_KEY_E)) m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel * 4.5f;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		IMPCT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(IMPCT_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent> (IMPCT_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(const MouseScrolledEvent& e)
	{
		IMPCT_PROFILE_FUNCTION();

		m_ZoomPower = Input::IsKeyPressed(IMPCT_KEY_LEFT_CONTROL)? m_ZoomPower = 2.0f : m_ZoomPower = 0.25f;

		m_ZoomLevel -= e.GetYOffset() * m_ZoomPower;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(const WindowResizeEvent& e)
	{
		IMPCT_PROFILE_FUNCTION();

		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}