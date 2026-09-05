#pragma once

#include "Impaction/Core/Core.h"
#include "Impaction/Core/Timestep.h"
#include "Impaction/Events/Event.h"

namespace impct
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		inline virtual void OnAttach() { }
		inline virtual void OnDetach() { }
		inline virtual void OnUpdate(Timestep timestep) { }
		inline virtual void OnImGuiRender() { }
		inline virtual void OnEvent(Event& event) { }
		
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}