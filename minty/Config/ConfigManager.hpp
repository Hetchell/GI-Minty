#pragma once
#include "../Json/json.hpp"

#include <string>

#include <iostream>
#include <fstream>

extern nlohmann::json cfgjsonobj;

void saveFuncStateToJson(std::string funcName, bool state);
void saveFuncStateToJson(std::string funcName, float state);
void saveFuncStateToJson(std::string funcName, int state);
bool readBoolFuncStateFromJson(std::string funcName);
int readHotkeyFromJson(std::string hotkeyName);
void saveHotkeyToJson(std::string hotkeyName, int hotkey);