#include "impct_pch.h"
#include "Layer.h"

namespace impct
{
	Layer::Layer(const std::string& debugName) 
		: m_DebugName(debugName) { }

	Layer::~Layer() { }
}