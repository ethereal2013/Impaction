#pragma once

#include "Impaction/Core.h"

namespace impct
{
	class Input
	{
	public:
		static inline bool IsKeyPressed(int keycode) 
		{ return s_Instance->IsKeyPressedImpl(keycode); }

		static inline bool IsMouseButtonPressed(int button) 
		{ return s_Instance->IsMouseButtonPressedImpl(button); }

		static inline float GetMouseX() 
		{ return s_Instance->GetMouseXImpl(); }

		static inline float GetMouseY() 
		{ return s_Instance->GetMouseYImpl(); }

		static inline std::pair<float, float> GetMousePos() 
		{ return s_Instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}