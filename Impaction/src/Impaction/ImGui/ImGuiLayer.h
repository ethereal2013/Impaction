#pragma once

#include "Impaction/Layer.h"

#include "Impaction/Events/KeyEvent.h"
#include "Impaction/Events/MouseEvent.h"
#include "Impaction/Events/ApplicationEvent.h"

namespace impct
{
	class IMPCT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}