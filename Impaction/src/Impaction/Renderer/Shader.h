#pragma once

#include <string>

namespace impct
{

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		//Initialize to stop warings in constructor.
		uint32_t m_RendererID = 0;
	};

}