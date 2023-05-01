#pragma once

#include <Windows.h>
#include <optional>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "../ImGui/ImGui/imgui.h"

namespace fs = std::filesystem;

static ImGuiTextBuffer log_textbuf;

namespace util {
    template<typename... Args>
    void log(int output_type, const char* fmt, Args... args) {
        const char* info_type[] = {"Warning", "Error", "Info", "Debug"};
        printf("[Minty:%s] ", info_type[output_type]);
        printf(fmt, args...);
        printf("\n");
        
        log_textbuf.appendf("[Minty:%s] ", info_type[output_type]);
        log_textbuf.appendf(fmt, args...);
        log_textbuf.appendf("\n");
    }
}