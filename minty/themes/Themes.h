#pragma once

#include "../api/imgui/ImGui/imgui.h"
#include "../config/ConfigManager.h"

static int fontindex_menu = 1;
static int theme_index = 1;
static int style_index = 1;

static ImVec4 wordle_empty = ImVec4(0.07058f, 0.07058f, 0.07450f, 1.0f);             // default = not guessed, dark grey
static ImVec4 wordle_guessed_noexist = ImVec4(0.22745f, 0.22745f, 0.23529f, 1.0f);   // 1 = guessed, letter doesnt exist, brighter grey
static ImVec4 wordle_guessed_wrongpos = ImVec4(0.70980f, 0.62352f, 0.23137f, 1.0f);  // 2 = guessed, letter exists but wrong position, yellow
static ImVec4 wordle_guessed_correct = ImVec4(0.32549f, 0.55294f, 0.30588f, 1.0f);   // 3 = guessed, letter exists and in right pos, green

void dark_theme();
void light_theme();
//void red_theme();

void cozy_style();
void cozy_square_style();

void setTheme(int themeIndex);
void setStyle(int styleIndex);
void setFont(int fontIndex);
