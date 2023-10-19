#pragma once

#define LOG(level, format, ...) Logger::log(level, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...) LOG(Logger::Level::Debug, format, __VA_ARGS__)
#define LOG_INFO(format, ...) LOG(Logger::Level::Info, format, __VA_ARGS__)
#define LOG_WARNING(format, ...) LOG(Logger::Level::Warning, format, __VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(Logger::Level::Error, format, __VA_ARGS__)

class Logger {
public:
	enum class Level {
		Debug,
		Info,
		Warning,
		Error,
	};

	static void log(Level logLevel, const char* format, ...);
};
