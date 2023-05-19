#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include <codecvt>
namespace {
    std::string il2cppi_to_string2(app::Il2CppString* str) {
        std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
        return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
    }

    std::string il2cppi_to_string3(app::String* str) {
        if (str == nullptr)
            return std::string("<nullptr>");
        return il2cppi_to_string2(reinterpret_cast<app::Il2CppString*>(str));
    }

    app::Vector3 operator + (const app::Vector3& A, const app::Vector3& B)
    {
        return { A.x + B.x, A.y + B.y, A.z + B.z };
    }

    app::Vector3 operator - (const app::Vector3& A, const app::Vector3& B)
    {
        return { A.x - B.x, A.y - B.y, A.z - B.z };
    }

    app::Vector3 operator * (const app::Vector3& A, const float k)
    {
        return { A.x * k, A.y * k, A.z * k };
    }
}
namespace il2fns {
    void OnNoclip(bool ifnoclip);
}