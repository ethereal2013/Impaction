#pragma once

#include "RendererAPI.h"

namespace impct
{

	class RenderCommand
	{
	public:
		inline static void Init() { s_RendererAPI->Init(); }
		
		inline static void SetClearColor(const glm::vec4 color) 
		{ return s_RendererAPI->SetClearColor(color); }

		inline static void Clear() { return s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) 
		{ return s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* s_RendererAPI;
	};

}