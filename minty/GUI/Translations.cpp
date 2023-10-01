#include "Translations.h"

string result;
static bool ifParse;
int LangTR = 0;

void InitTR() {
    HMODULE hModule = GetModuleHandle("minty.dll");
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(IDR_RCDATA2), RT_RCDATA);

    if (hResource)
    {
        HGLOBAL hData = LoadResource(hModule, hResource);
        if (hData)
        {
            DWORD dataSize = SizeofResource(hModule, hResource);
            char* data = (char*)LockResource(hData);
            result.assign(data, dataSize);
        }
    }
}

u8string u8result;
const char* _(string code) {
    /*nlohmann::json trJson;
    if (result == "") {
        InitTR();
    }
    string retStr;
    trJson = nlohmann::json::parse(result);
    switch (LangTR) {
    case 0:
        retStr = trJson["EN"][code];
        break;
    case 1:
        retStr = trJson["RU"][code];
        break;
    case 2:
        retStr = trJson["CN"][code];
        break;
    case 3:
        retStr = trJson["ID"][code];
        break;
    default:
        retStr = trJson["EN"][code];
        break;
    }
    u8result = u8string(retStr.begin(), retStr.end());
    return reinterpret_cast<const char*>(u8result.c_str());*/
    return code.c_str();
}