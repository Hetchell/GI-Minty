#pragma once
#include <iomanip>
#include <sstream>

#include "../ImGui/ImGui/imgui.h"
// #include "../IL2CPP/il2cpp-init.hpp"
// #include "../IL2CPP/il2cpp-appdata.h"

static ImGuiTextBuffer log_textbuf;

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
    const char* info_type[] = {"Debug", "Info", "Warning", "Error"};

    printf("[Minty:%s] ", info_type[static_cast<int>(output_type)]);
    printf(fmt, args...);
    printf("\n");

    log_textbuf.appendf("[Minty:%s] ", info_type[static_cast<int>(output_type)]);
    log_textbuf.appendf(fmt, args...);
    log_textbuf.appendf("\n");
}
/*
 uintptr_t PatternScan(LPCSTR module, LPCSTR pattern)
{
	static auto pattern_to_byte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);
		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto mod = GetModuleHandle(module);
	if (!mod)
		return 0;

	auto dosHeader = (PIMAGE_DOS_HEADER)mod;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)mod + dosHeader->e_lfanew);
	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(pattern);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(mod);
	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			return (uintptr_t)&scanBytes[i];
		}
	}
	return 0;
}

 template< typename T >
 std::string int_to_hex(T i) {
 	std::stringstream stream;
 	stream << "0x"
 		<< std::setfill('0') << std::setw(sizeof(T) * 2)
 		<< std::hex << i;
 	return stream.str();
 }

 void DumpAddress(uint32_t start, long magic_a, long magic_b)
{
	uintptr_t baseAddress = (uintptr_t)GetModuleHandle("UserAssembly.dll");
	if (baseAddress != (uintptr_t)nullptr) {
		//for (uint32_t i = start; ; i++)
		for (unsigned int i = start; ; i++)
		{
			auto klass = il2cpp__vm__MetadataCache__GetTypeInfoFromTypeDefinitionIndex(i);
			if (klass != nullptr) {
				std::string result = "klass defined: %s\n defining classname";
				util::log(2, result.c_str());
				// &reinterpret_cast<uintptr_t*>(klass)[?] is a magic for klass->byval_arg
				std::string class_name = il2cpp__vm__Type__GetName(&reinterpret_cast<intptr_t*>(klass)[26], 0);
				if (class_name != (std::string)nullptr) {
					util::log(2, "classname defined\n trying to log");
					//util::Log("[%d]\n%s", i, class_name.c_str());
					void* iter = 0;
					util::log(2, "tryin to getmethod..");
					while (const LPVOID method = il2cpp__vm__Class__GetMethods(klass, (LPVOID)&iter))
					{
						if (method != nullptr) {
							util::log(2, "got method");
							// &reinterpret_cast<uintptr_t*>(method)[?] is a magic for method->methodPointer
							auto method_address = reinterpret_cast<uintptr_t*>(method)[magic_b];
							if (method_address != (uintptr_t)nullptr) {
								if (method_address)
									method_address -= baseAddress;
								std::string method_name = il2cpp__vm__Method__GetNameWithGenericTypes(method);
								if (method_name != (std::string)method_name) {
									util::Flogf("\t0x%08X: %s", method_address, method_name.c_str());
								}
								else
									util::log(2, "method name null");
							}
							else
								util::log(2, "method address null");
						}
						else
							util::log(2, "method null");
					}
				}
				else
					util::log(2, "class name null");
			}
			else
				util::log(2, "klass null");
			//util::Flogf("");
		}
	}
 }
 */
}  // namespace util