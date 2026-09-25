#pragma once

#include "Impaction/Core/Window.h"
#include <GLFW/glfw3.h>

#include "Impaction/Renderer/GraphicsContext.h"

namespace impct
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		void OnUpdate() override;

		[[nodiscard]] inline unsigned int GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override
			{ m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override;

		[[nodiscard]] inline void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}