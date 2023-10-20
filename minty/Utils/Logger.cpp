#include "Logger.h"

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cstdarg>
#include <fstream>
#include <filesystem>

struct Prefix {
	char color;
	const char* text;
};

Prefix getLevelPrefix(Logger::Level level) {
	switch (level) {
	case Logger::Level::Error:
		return { 0x0C, "Error" };
	case Logger::Level::Warning:
		return { 0x06, "Warning" };
	case Logger::Level::Info:
		return { 0x02, "Info" };
	case Logger::Level::Debug:
		return { 0x0B, "Debug" };
	default:
		return { 0x00, "" };
	}
}

void Logger::log(Logger::Level logLevel, const char* format, ...) {
	char buffer[4096];

	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, format, args);
	va_end(args);

	auto prefix = getLevelPrefix(logLevel);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "[Minty:";
	SetConsoleTextAttribute(hConsole, prefix.color);
	std::cout << prefix.text;
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "] " << buffer << "\n";
}
