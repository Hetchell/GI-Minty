#pragma once
#include "../Utils/Utils.hpp"
#include "../Functions/Function.h"
/*----------GUI----------*/
static bool g_ShowMenu = true;
static bool block_input = true;
//static bool ifshowfps = true;
static bool show_debug_metrics;
static bool show_style_editor;
static bool show_debug_log;
static bool show_lua_editor = false;
extern bool show_rpc;
extern int init_delay;

static std::vector<std::unique_ptr<FN>> All_vec;
/*----------THEME----------*/

/*----------LUA----------*/

/*----------IL2CPP----------*/

//extern bool is_il2cpp_hooked = false;

#define PUSH_FUNC(name) std::unique_ptr<cheat::##name> name = std::make_unique<cheat::name>(); \
All_vec.push_back(std::move(name));

#define CheckBoxFN(name, var, cfgName) if (ImGui::Checkbox(##name, &##var##)) config::setValue("functions", ##cfgName, ##var);