#pragma once

#include <string>
#include <vector>

extern std::vector<std::string> ModuleOrder;

void Outer();

void Init();

void DrawSection(const std::string& sectionName);