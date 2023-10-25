#pragma once

#include <string>
#include <vector>

extern std::vector<std::string> ModuleOrder;

void Init();
void Outer();

void DrawSection(const std::string& sectionName);
