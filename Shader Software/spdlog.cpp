#include "spdlog.h"

namespace apf
{
	std::shared_ptr<spdlog::logger> apfLog::s_CoreLogger;
	std::shared_ptr<spdlog::logger> apfLog::s_ClientLogger;
	std::shared_ptr<spdlog::logger> apfLog::s_BaseSpdlogInformation;

	void apfLog::Init()
	{
		spdlog::set_pattern("%^[%T] [%n]: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("EngineInfo");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("DebugInfo");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_BaseSpdlogInformation = spdlog::basic_logger_mt<spdlog::async_factory>("async_logger", "C:/Apricot Fish Engine/Spdlog_Information/async_log.txt");
		s_BaseSpdlogInformation->set_level(spdlog::level::trace);
	}
}