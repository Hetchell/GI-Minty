#pragma once

#include <Windows.h>

#include "../resource.h"
#include "../includes.h"
#include "../api/json/json.hpp"

// 0 - EN, 1 - RU, 2 - CN, 3 - ID
extern int LangTR;
const char* _(const char* code);
