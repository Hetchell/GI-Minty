#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../HookManager.h"
#include <codecvt>
namespace {
    std::string il2cppi_to_string(app::Il2CppString* str) {
        std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
        return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
    }

    std::string il2cppi_to_string(app::String* str) {
        if (str == nullptr)
            return std::string("<nullptr>");
        return il2cppi_to_string(reinterpret_cast<app::Il2CppString*>(str));
    }
    app::String* string_to_il2cppii(std::string input) {
        return app::Marshal_PtrToStringAnsi((void*)input.c_str());
    }
}
namespace il2fns {
	void LCAvatarCombat_NoCD(bool value);
    void NoBowCD(bool value);
}