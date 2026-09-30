#pragma once

#include "impct_pch.h"
#include "Event.h"

namespace impct
{
	class MouseMovedEvent : public Event
	{
	public:
		inline MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) { }

		[[nodiscard]] inline float GetX() const { return m_MouseX; }
		[[nodiscard]] inline float GetY() const { return m_MouseY; }

		[[nodiscard]] inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		inline MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) { }

		[[nodiscard]] inline float GetXOffset() const { return m_XOffset; }
		[[nodiscard]] inline float GetYOffset() const { return m_YOffset; }

		[[nodiscard]] inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		[[nodiscard]] inline int GetMouseButton() const { return m_MouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		inline MouseButtonEvent(const int button) : m_MouseButton(button) { }
		int m_MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		inline MouseButtonPressedEvent(const int button)
			: MouseButtonEvent(button) {}

		[[nodiscard]] inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		inline MouseButtonReleasedEvent(const int button)
			: MouseButtonEvent(button) { }

		[[nodiscard]] inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}