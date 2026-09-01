#pragma once

#include <string>

namespace impct
{

	class Shader
	{
	public:
		inline virtual ~Shader() noexcept = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] static Ref<Shader> Create(const std::string& filepath);
		[[nodiscard]] static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}