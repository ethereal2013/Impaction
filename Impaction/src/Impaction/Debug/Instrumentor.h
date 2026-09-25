#pragma once

#ifdef IMPCT_DEBUG

#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>

#include <thread>

namespace impct
{

	struct ProfileResult
	{
		std::string Name;
		int64_t Start, End;
		uint64_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		inline Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{
		}

		inline void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		inline void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		inline void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0) m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream
				<< "{\n"
				<< "\t\"cat\": \"function\",\n"
				<< "\t\"dur\": " << (result.End - result.Start) << ",\n"
				<< "\t\"name\": \"" << name << "\",\n"
				<< "\t\"ph\": \"X\",\n"
				<< "\t\"pid\": 0,\n"
				<< "\t\"tid\": " << result.ThreadID << ",\n"
				<< "\t\"ts\": " << result.Start << "\n"
				<< "}";

			m_OutputStream.flush();
		}

		inline void WriteHeader()
		{
			m_OutputStream << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n";
			m_OutputStream.flush();
		}

		inline void WriteFooter()
		{
			m_OutputStream << "\n\t]\n}";
			m_OutputStream.flush();
		}

		static inline Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};

	class InstrumentationTimer
	{
	public:
		inline InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		inline ~InstrumentationTimer() { if (!m_Stopped) Stop(); }

		inline void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint64_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}

	private:
		const char* m_Name;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	};

}

#define IMPCT_PROFILE 1

#if IMPCT_PROFILE

	#if defined(_MSC_VER)
		#define IMPCT_FUNCTION_SIGNATURE __FUNCSIG__
	#elif defined(__GNUC__) || defined(__clang__) 
		#define IMPCT_FUNCTION_SIGNATURE __PRETTY_FUNCTION__ 
	#else
		#define IMPCT_FUNCTION_SIGNATURE __func__ 
	#endif 

	#define IMPCT_DETAIL_CONCAT(a, b) a##b 

	#define IMPCT_PROFILE_BEGIN_SESSION(name, filepath) ::impct::Instrumentor::Get().BeginSession(name, filepath) 
	#define IMPCT_PROFILE_END_SESSION()					::impct::Instrumentor::Get().EndSession()
	#define IMPCT_PROFILE_SCOPE(name)					::impct::InstrumentationTimer IMPCT_DETAIL_CONCAT(impct_profile_timer_, __LINE__)(name)
	#define IMPCT_PROFILE_FUNCTION()  IMPCT_PROFILE_SCOPE(IMPCT_FUNCTION_SIGNATURE)

#else
	#define IMPCT_PROFILE_BEGIN_SESSION(name, filepath)
	#define IMPCT_PROFILE_END_SESSION()
	#define IMPCT_PROFILE_SCOPE(name)
	#define IMPCT_PROFILE_FUNCTION()

#endif

#else
	#define IMPCT_PROFILE_BEGIN_SESSION(name, filepath)
	#define IMPCT_PROFILE_END_SESSION()
	#define IMPCT_PROFILE_SCOPE(name)
	#define IMPCT_PROFILE_FUNCTION()

#endif
