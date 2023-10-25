#pragma once

#include <iomanip>
#include <sstream>

namespace util {
	template <typename T>
	const char* get_ptr(const T& value) {
		std::stringstream ss;
		ss << std::hex << std::showbase << reinterpret_cast<const void*>(value);
		static std::string result = ss.str();
		return result.c_str();
	}
}
