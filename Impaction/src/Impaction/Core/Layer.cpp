#include "impct_pch.h"
#include "Layer.h"

#include <utility>

namespace impct
{
	Layer::Layer(std::string name)
		: m_DebugName(std::move(name)) { }

	Layer::~Layer() = default;
}