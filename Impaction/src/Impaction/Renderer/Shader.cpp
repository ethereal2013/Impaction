#include "impct_pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace impct
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return MakeRef<OpenGLShader>(filepath);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				IMPCT_CORE_ASSERT(false, "RendererAPI::None is not defined!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return MakeRef<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		IMPCT_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}


}