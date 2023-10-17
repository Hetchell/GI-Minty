#pragma once

#include "../Utils/Utils.hpp"
#include "../Functions/Function.h"

static bool g_ShowMenu = true;
static bool block_input = true;
static bool show_style_editor;
static bool show_lua_editor = false;

static std::vector<Function*> functions;

#define INIT_FUNC(function) functions.push_back(&cheat::##function##::getInstance());
