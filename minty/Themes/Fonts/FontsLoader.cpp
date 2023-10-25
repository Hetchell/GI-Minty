#include <Windows.h>
#include <optional>
#include <libloaderapi.h>

#include "FontsLoader.h"

bool LoadFontFromResources(ImFontConfig font_cfg, const wchar_t* fontName, float fontSize) {
    HMODULE hModuleF = GetModuleHandle("minty.dll");
    //HMODULE hModuleF;
    // Find the resource handle within the DLL
    HRSRC hResource = FindResource(hModuleF, (LPCSTR)fontName, RT_RCDATA);
    if (!hResource)
    {
        // Resource not found
        return false;
    }

    // Load the resource data
    HGLOBAL hMemory = LoadResource(hModuleF, hResource);
    if (!hMemory)
    {
        // Failed to load resource
        return false;
    }

    // Get the resource data pointer and size
    LPVOID pData = LockResource(hMemory);
    DWORD dataSize = SizeofResource(hModuleF, hResource);

    // Create a memory buffer for the font data
    font_cfg.FontDataOwnedByAtlas = false; // We'll keep the memory until ImGui is shut down
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(pData, dataSize, fontSize, &font_cfg);

    // Clean up the resource handles
    UnlockResource(hMemory);
    FreeResource(hMemory);

    return true;
}
