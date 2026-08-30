#pragma once

#include <string>
#include <Impaction/Core.h>

namespace impct
{

	class Texture
	{
	public:
		inline virtual ~Texture() noexcept = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		[[nodiscard]] static Ref<Texture2D> Create(const std::string& path);
	};

}