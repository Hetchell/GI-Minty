#include "il2cppUtils.h"
#include <codecvt>

/*
std::string il2cppi_to_string(app::Il2CppString* str) {
    int32_t length = str->length;
    const char* chars = reinterpret_cast<const char*>(str->chars);
    return std::string(chars, chars + length);
}
*/

std::string il2cppi_to_string(app::Il2CppString* str) {
    std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

std::string il2cppi_to_string(app::String* str) {
    if (str == nullptr)
        return std::string("<nullptr>");
    return il2cppi_to_string(reinterpret_cast<app::Il2CppString*>(str));
}

app::String* string_to_il2cppi(std::string input) {
    return app::Marshal_PtrToStringAnsi((void*)input.c_str());
}

app::String* string_to_il2cppi(const char* input) {
    return app::Marshal_PtrToStringAnsi((void*)input);
}
