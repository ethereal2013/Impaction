#include <impct_pch.h>

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace impct
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}