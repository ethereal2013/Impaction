#include "impct_pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace impct
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return MakeRef<OpenGLTexture2D>(width, height);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return MakeRef<OpenGLTexture2D>(path);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}