#include "LuaUtils.h"

namespace fs = std::filesystem;

const PIMAGE_SECTION_HEADER get_section_by_name(HMODULE base, const char* name) {
    const PIMAGE_DOS_HEADER hdos = (PIMAGE_DOS_HEADER)base;
    const PIMAGE_NT_HEADERS hpe = (PIMAGE_NT_HEADERS)((PBYTE)hdos + hdos->e_lfanew);
    const PIMAGE_SECTION_HEADER sections = IMAGE_FIRST_SECTION(hpe);
    for (int i = 0; i < hpe->FileHeader.NumberOfSections; i++) {
        if (strcmp((const char*)sections[i].Name, name) == 0) {
            return &sections[i];
        }
    }
    return NULL;
}

uintptr_t PatternScan(LPCSTR module, LPCSTR pattern) {
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		//for (auto& b : bytes) Utils::ConsolePrint("%02x ", b);
		return bytes;
	};

	auto mod = GetModuleHandleA(module);

	if (!mod)
		return 0;

	auto dosHeader = (PIMAGE_DOS_HEADER)mod;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)mod + dosHeader->e_lfanew);
	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(pattern);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(mod);
	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}

		if (found) {
			return (uintptr_t)&scanBytes[i];
		}
	}
	return 0;
}

bool cmp_pat(const uint8_t* pat, const char* mask, size_t pattern_len, const uint8_t* ptr) {
    for (int i = 0; i < pattern_len; i++)
        if (mask[i] == 'x' && pat[i] != ptr[i])
            return false;

    return true;
}

const uint8_t* find_pat(const uint8_t* pat, const char* mask, const uint8_t* start, size_t size, bool reverse) {
    auto pattern_len = strlen(mask);
    auto end = start + size - pattern_len;

    if (reverse) {
        for (auto ptr = end; ptr >= start; ptr--)
            if (cmp_pat(pat, mask, pattern_len, ptr) == true)
                return ptr;
    } else {
        for (auto ptr = start; ptr <= end; ptr++)
            if (cmp_pat(pat, mask, pattern_len, ptr) == true)
                return ptr;
    }
    return 0;
}

const uint8_t* find_ref_relative(const uint8_t* addr, const uint8_t* start, size_t size, bool reverse) {
    auto end = start + size - 4;

    if (reverse) {
        for (auto ptr = end; ptr >= start; ptr--)
            if (*(uint32_t*)(ptr) + ptr + 4 == addr)
                return ptr;
    } else {
        for (auto ptr = start; ptr <= end; ptr++)
            if (*(uint32_t*)(ptr) + ptr + 4 == addr)
                return ptr;
    }
    return 0;
}
