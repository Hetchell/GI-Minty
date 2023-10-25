#pragma once

#include <Windows.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>

#include "../api/imgui/ImGui/imgui.h"

const PIMAGE_SECTION_HEADER get_section_by_name(HMODULE base, const char* name);
uintptr_t PatternScan(LPCSTR module, LPCSTR pattern);
bool cmp_pat(const uint8_t* pat, const char* mask, size_t pattern_len, const uint8_t* ptr);
const uint8_t* find_pat(const uint8_t* pat, const char* mask, const uint8_t* start, size_t size, bool reverse = false);
const uint8_t* find_ref_relative(const uint8_t* addr, const uint8_t* start, size_t size, bool reverse = false);
