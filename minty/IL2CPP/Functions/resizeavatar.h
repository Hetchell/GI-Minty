#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
// #define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
// #define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

namespace il2fns {
	void Resize__Avatar(float scale);
}

namespace {
    std::string il2cpp_to_string(app::Il2CppString* str) {
        int32_t length = str->length;
        const char* chars = reinterpret_cast<const char*>(str->chars);
        return std::string(chars, chars + length);
    }
}