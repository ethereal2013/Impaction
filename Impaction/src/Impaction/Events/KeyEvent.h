#pragma once

#include <impct_pch.h>
#include "Event.h"

namespace impct
{
	//Base class
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		inline KeyEvent(int keycode) : m_KeyCode(keycode) { }
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		inline KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		inline virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		inline KeyReleasedEvent(int keycode) : KeyEvent(keycode) { }

		inline virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		inline KeyTypedEvent(int keycode) : KeyEvent(keycode) { }

		inline virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}