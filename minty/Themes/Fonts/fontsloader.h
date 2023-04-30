#pragma once
#include <Windows.h>

HMODULE hModule = GetModuleHandle(NULL);
HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(IDR_MY_FONT), _T("FONT"));
HGLOBAL hResourceData = LoadResource(hModule, hResource);
const void* fontData = LockResource(hResourceData);
DWORD fontDataSize = SizeofResource(hModule, hResource);
