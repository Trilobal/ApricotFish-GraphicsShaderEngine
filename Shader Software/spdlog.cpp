#include "spdlog.h"

namespace apf
{
	std::shared_ptr<spdlog::logger> apfLog::s_CoreLogger;
	std::shared_ptr<spdlog::logger> apfLog::s_ClientLogger;

	void apfLog::Init()
	{
		spdlog::set_pattern("%^[%T] [%n]: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("EngineInfo");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("DebugInfo");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}