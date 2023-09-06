#pragma once

#include <iomanip>
#include <sstream>
#include <vector>

enum MLogType {
    M_Debug,
    M_Info,
    M_Warning,
    M_Error,
};

namespace util {
	template <typename T>
	const char* get_ptr(const T& value) {
		std::stringstream ss;
		ss << std::hex << std::showbase << reinterpret_cast<const void*>(value);
		static std::string result = ss.str();
		return result.c_str();
	}

	template <typename... Args>
	void log(MLogType output_type, const char* fmt, Args... args) {
		const char* info_type[] = { "Debug", "Info", "Warning", "Error" };

		printf("[Minty:%s] ", info_type[static_cast<int>(output_type)]);
		printf(fmt, args...);
		printf("\n");
	}

	template<typename T>
	std::string int_to_hex(T i) {
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(sizeof(T) * 2)
			<< std::hex << i;
		return stream.str();
	}
}
