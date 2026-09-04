#pragma once

#include "RendererAPI.h"

namespace impct
{

	class RenderCommand
	{
	public:
		static inline void Init() { s_RendererAPI->Init(); }

		static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{ return s_RendererAPI->SetViewport(x, y, width, height); }
		
		static inline void SetClearColor(const glm::vec4 color) 
		{ return s_RendererAPI->SetClearColor(color); }

		static inline void Clear() { return s_RendererAPI->Clear(); }

		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray) 
		{ return s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* s_RendererAPI;
	};

}