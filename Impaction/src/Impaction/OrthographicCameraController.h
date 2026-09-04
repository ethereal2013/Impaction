#pragma once

#include <glm/glm.hpp>

#include "Impaction/Renderer/OrthographicCamera.h"
#include "Impaction/Core/Timestep.h"

#include "Impaction/Events/ApplicationEvent.h"
#include "Impaction/Events/MouseEvent.h"

namespace impct
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		float m_CameraRotation = 0.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 4.5f, m_CameraRotationSpeed = 180.0f;
	};

}