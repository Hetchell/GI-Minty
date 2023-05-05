#pragma once
#include <sstream>
#include <iomanip>
#include "../ImGui/ImGui/imgui.h"

static ImGuiTextBuffer log_textbuf;
namespace util {
    
    template <typename T>
    const char* get_ptr(const T& value) {
        std::stringstream ss;
        ss << std::hex << std::showbase << reinterpret_cast<const void*>(value);
        static std::string result = ss.str();
        return result.c_str();
    }
    
	template<typename... Args>
	void log(int output_type, const char* fmt, Args... args) {
		const char* info_type[] = { "Warning", "Error", "Info", "Debug", "Lua" };
		printf("[Minty:%s] ", info_type[output_type]);
		printf(fmt, args...);
		printf("\n");

		log_textbuf.appendf("[Minty:%s] ", info_type[output_type]);
		log_textbuf.appendf(fmt, args...);
		log_textbuf.appendf("\n");
	}
}