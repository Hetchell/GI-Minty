#pragma once

#include "il2cpp-appdata.h"
#include "il2cpp-types.h"

std::string il2cppi_to_string(app::Il2CppString* str);
std::string il2cppi_to_string(app::String* str);
app::String* string_to_il2cppi(std::string input);
app::String* string_to_il2cppi(const char* input);

app::Vector3 operator + (const app::Vector3& A, const app::Vector3& B);
app::Vector3 operator - (const app::Vector3& A, const app::Vector3& B);
app::Vector3 operator * (const app::Vector3& A, const float k);