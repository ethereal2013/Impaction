#pragma once

#include "RendererAPI.h"

namespace impct
{

	class RenderCommand
	{
	public:
		static inline void Init() { IMPCT_PROFILE_FUNCTION(); s_RendererAPI->Init(); }

		static inline void SetViewport(uint32_t x, uint32_t y, const uint32_t width, const uint32_t height)
		{ return s_RendererAPI->SetViewport(x, y, width, height); }
		
		static inline void SetClearColor(const glm::vec4 color) 
		{ return s_RendererAPI->SetClearColor(color); }

		static inline void Clear() { return s_RendererAPI->Clear(); }

		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount = 0)
		{ return s_RendererAPI->DrawIndexed(vertexArray, indexCount); }

	private:
		static RendererAPI* s_RendererAPI;
	};

}