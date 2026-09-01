#include "impct_pch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace impct
{

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}

		IMPCT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return MakeRef<OpenGLVertexBuffer>(vertices, size);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return MakeRef<OpenGLIndexBuffer>(indices, count);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}