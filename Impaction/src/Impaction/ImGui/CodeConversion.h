#include <impct_pch.h>

#include "Impaction/KeyCodes.h"

#include "Impaction/Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace impct
{
	inline static ImGuiKey GLFWToImGui(int key)
	{
		switch (key)
		{

			// Printable keys
			case IMPCT_KEY_SPACE:         return ImGuiKey_Space;
			case IMPCT_KEY_APOSTROPHE:    return ImGuiKey_Apostrophe;
			case IMPCT_KEY_COMMA:         return ImGuiKey_Comma;
			case IMPCT_KEY_MINUS:         return ImGuiKey_Minus;
			case IMPCT_KEY_PERIOD:        return ImGuiKey_Period;
			case IMPCT_KEY_SLASH:         return ImGuiKey_Slash;
			case IMPCT_KEY_SEMICOLON:     return ImGuiKey_Semicolon;
			case IMPCT_KEY_EQUAL:         return ImGuiKey_Equal;
			case IMPCT_KEY_LEFT_BRACKET:  return ImGuiKey_LeftBracket;
			case IMPCT_KEY_BACKSLASH:     return ImGuiKey_Backslash;
			case IMPCT_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
			case IMPCT_KEY_GRAVE_ACCENT:  return ImGuiKey_GraveAccent;


			// Numbers
			case IMPCT_KEY_0: return ImGuiKey_0;
			case IMPCT_KEY_1: return ImGuiKey_1;
			case IMPCT_KEY_2: return ImGuiKey_2;
			case IMPCT_KEY_3: return ImGuiKey_3;
			case IMPCT_KEY_4: return ImGuiKey_4;
			case IMPCT_KEY_5: return ImGuiKey_5;
			case IMPCT_KEY_6: return ImGuiKey_6;
			case IMPCT_KEY_7: return ImGuiKey_7;
			case IMPCT_KEY_8: return ImGuiKey_8;
			case IMPCT_KEY_9: return ImGuiKey_9;

			// Alphabet
			case IMPCT_KEY_A: return ImGuiKey_A;
			case IMPCT_KEY_B: return ImGuiKey_B;
			case IMPCT_KEY_C: return ImGuiKey_C;
			case IMPCT_KEY_D: return ImGuiKey_D;
			case IMPCT_KEY_E: return ImGuiKey_E;
			case IMPCT_KEY_F: return ImGuiKey_F;
			case IMPCT_KEY_G: return ImGuiKey_G;
			case IMPCT_KEY_H: return ImGuiKey_H;
			case IMPCT_KEY_I: return ImGuiKey_I;
			case IMPCT_KEY_J: return ImGuiKey_J;
			case IMPCT_KEY_K: return ImGuiKey_K;
			case IMPCT_KEY_L: return ImGuiKey_L;
			case IMPCT_KEY_M: return ImGuiKey_M;
			case IMPCT_KEY_N: return ImGuiKey_N;
			case IMPCT_KEY_O: return ImGuiKey_O;
			case IMPCT_KEY_P: return ImGuiKey_P;
			case IMPCT_KEY_Q: return ImGuiKey_Q;
			case IMPCT_KEY_R: return ImGuiKey_R;
			case IMPCT_KEY_S: return ImGuiKey_S;
			case IMPCT_KEY_T: return ImGuiKey_T;
			case IMPCT_KEY_U: return ImGuiKey_U;
			case IMPCT_KEY_V: return ImGuiKey_V;
			case IMPCT_KEY_W: return ImGuiKey_W;
			case IMPCT_KEY_X: return ImGuiKey_X;
			case IMPCT_KEY_Y: return ImGuiKey_Y;
			case IMPCT_KEY_Z: return ImGuiKey_Z;


			// Function keys
			case IMPCT_KEY_F1:  return ImGuiKey_F1;
			case IMPCT_KEY_F2:  return ImGuiKey_F2;
			case IMPCT_KEY_F3:  return ImGuiKey_F3;
			case IMPCT_KEY_F4:  return ImGuiKey_F4;
			case IMPCT_KEY_F5:  return ImGuiKey_F5;
			case IMPCT_KEY_F6:  return ImGuiKey_F6;
			case IMPCT_KEY_F7:  return ImGuiKey_F7;
			case IMPCT_KEY_F8:  return ImGuiKey_F8;
			case IMPCT_KEY_F9:  return ImGuiKey_F9;
			case IMPCT_KEY_F10: return ImGuiKey_F10;
			case IMPCT_KEY_F11: return ImGuiKey_F11;
			case IMPCT_KEY_F12: return ImGuiKey_F12;
			case IMPCT_KEY_F13: return ImGuiKey_F13;
			case IMPCT_KEY_F14: return ImGuiKey_F14;
			case IMPCT_KEY_F15: return ImGuiKey_F15;
			case IMPCT_KEY_F16: return ImGuiKey_F16;
			case IMPCT_KEY_F17: return ImGuiKey_F17;
			case IMPCT_KEY_F18: return ImGuiKey_F18;
			case IMPCT_KEY_F19: return ImGuiKey_F19;
			case IMPCT_KEY_F20: return ImGuiKey_F20;
			case IMPCT_KEY_F21: return ImGuiKey_F21;
			case IMPCT_KEY_F22: return ImGuiKey_F22;
			case IMPCT_KEY_F23: return ImGuiKey_F23;
			case IMPCT_KEY_F24: return ImGuiKey_F24;


			// Navigation / editing
			case IMPCT_KEY_TAB:        return ImGuiKey_Tab;
			case IMPCT_KEY_LEFT:       return ImGuiKey_LeftArrow;
			case IMPCT_KEY_RIGHT:      return ImGuiKey_RightArrow;
			case IMPCT_KEY_UP:         return ImGuiKey_UpArrow;
			case IMPCT_KEY_DOWN:       return ImGuiKey_DownArrow;

			case IMPCT_KEY_PAGE_UP:    return ImGuiKey_PageUp;
			case IMPCT_KEY_PAGE_DOWN:  return ImGuiKey_PageDown;
			case IMPCT_KEY_HOME:       return ImGuiKey_Home;
			case IMPCT_KEY_END:        return ImGuiKey_End;

			case IMPCT_KEY_INSERT:     return ImGuiKey_Insert;
			case IMPCT_KEY_DELETE:     return ImGuiKey_Delete;
			case IMPCT_KEY_BACKSPACE:  return ImGuiKey_Backspace;
			case IMPCT_KEY_ENTER:      return ImGuiKey_Enter;
			case IMPCT_KEY_ESCAPE:     return ImGuiKey_Escape;

			// Lock / system keys
			case IMPCT_KEY_CAPS_LOCK:   return ImGuiKey_CapsLock;
			case IMPCT_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
			case IMPCT_KEY_NUM_LOCK:    return ImGuiKey_NumLock;

			case IMPCT_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
			case IMPCT_KEY_PAUSE:         return ImGuiKey_Pause;
			case IMPCT_KEY_MENU:          return ImGuiKey_Menu;


			// Modifiers
			case IMPCT_KEY_LEFT_SHIFT:    return ImGuiKey_LeftShift;
			case IMPCT_KEY_RIGHT_SHIFT:   return ImGuiKey_RightShift;

			case IMPCT_KEY_LEFT_CONTROL:  return ImGuiKey_LeftCtrl;
			case IMPCT_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;

			case IMPCT_KEY_LEFT_ALT:      return ImGuiKey_LeftAlt;
			case IMPCT_KEY_RIGHT_ALT:     return ImGuiKey_RightAlt;

			case IMPCT_KEY_LEFT_SUPER:    return ImGuiKey_LeftSuper;
			case IMPCT_KEY_RIGHT_SUPER:   return ImGuiKey_RightSuper;

			// Keypad
			case IMPCT_KEY_KP_0:         return ImGuiKey_Keypad0;
			case IMPCT_KEY_KP_1:         return ImGuiKey_Keypad1;
			case IMPCT_KEY_KP_2:         return ImGuiKey_Keypad2;
			case IMPCT_KEY_KP_3:         return ImGuiKey_Keypad3;
			case IMPCT_KEY_KP_4:         return ImGuiKey_Keypad4;
			case IMPCT_KEY_KP_5:         return ImGuiKey_Keypad5;
			case IMPCT_KEY_KP_6:         return ImGuiKey_Keypad6;
			case IMPCT_KEY_KP_7:         return ImGuiKey_Keypad7;
			case IMPCT_KEY_KP_8:         return ImGuiKey_Keypad8;
			case IMPCT_KEY_KP_9:         return ImGuiKey_Keypad9;

			case IMPCT_KEY_KP_DECIMAL:   return ImGuiKey_KeypadDecimal;
			case IMPCT_KEY_KP_DIVIDE:    return ImGuiKey_KeypadDivide;
			case IMPCT_KEY_KP_MULTIPLY:  return ImGuiKey_KeypadMultiply;
			case IMPCT_KEY_KP_SUBTRACT:  return ImGuiKey_KeypadSubtract;
			case IMPCT_KEY_KP_ADD:       return ImGuiKey_KeypadAdd;
			case IMPCT_KEY_KP_ENTER:     return ImGuiKey_KeypadEnter;
			case IMPCT_KEY_KP_EQUAL:     return ImGuiKey_KeypadEqual;

			// Unsupported / unknown GLFW keys
			case IMPCT_KEY_WORLD_1:
			case IMPCT_KEY_WORLD_2:
			case IMPCT_KEY_UNKNOWN:

			default: return ImGuiKey_None;
		}
	}
}