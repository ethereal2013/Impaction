#pragma once

namespace impct
{

	class Timestep
	{
	public:
		inline Timestep(const float time = 0.0f)
			: m_Time(time)
		{
		}

		inline operator float() const { return m_Time; }

		[[nodiscard]] inline float GetSeconds() const { return m_Time; }
		[[nodiscard]] inline float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};

}