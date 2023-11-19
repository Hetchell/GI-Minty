#pragma once

#include "../functions/Function.h"

static bool show_style_editor;
static bool show_lua_editor = false;

static std::vector<Function*> functions;

#define INIT_FUNC(function) functions.push_back(&cheat::##function##::getInstance());
