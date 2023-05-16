#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"

#define WIN32_LEAN_AND_MEAN

#include <codecvt>
#include <Psapi.h>

#if _MSC_VER >= 1920
namespace {
    std::string il2cppi_to_string(app::Il2CppString* str) {
        std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
        return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
    }
//std::string il2cppi_to_string(app::Il2CppString* str) {
//    const char16_t* u16 = reinterpret_cast<const char16_t*>(str->chars);
//    int u16Length = wcslen(reinterpret_cast<const wchar_t*>(u16));
//    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(u16), u16Length, nullptr, 0, nullptr, nullptr);
//    std::string utf8(utf8Length, '\0');
//    WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(u16), u16Length, &utf8[0], utf8Length, nullptr, nullptr);
//    return utf8;
//}

std::string il2cppi_to_string(app::String* str) {
    if (str == nullptr)
        return std::string("<nullptr>");
    return il2cppi_to_string(reinterpret_cast<app::Il2CppString*>(str));
}
}
#endif

namespace il2fns {
	void ScaleBreast();
}