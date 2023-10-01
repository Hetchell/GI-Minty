#include "Hotkey.h"
#include "KeyBind.h"
#include "../ImGui/ImGui/imgui.h"
#include <Windows.h>
#include <thread>

Hotkey::Hotkey()
{
    hotkeyJsonName = "";
    this->m_nHkey = 0;
    this->bWaitsInput = false;
}

Hotkey::Hotkey(const char* jsonStateName)
{
    this->m_nHkey = readHotkeyFromJson(jsonStateName);
    this->hotkeyJsonName = jsonStateName;
    this->bWaitsInput = false;
}

bool Hotkey::IsPressed()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastInputTime).count() > 100 && ImGui::IsKeyPressed(static_cast<ImGuiKey>(this->m_nHkey), false);
}

bool Hotkey::IsDown()
{
	return ImGui::IsKeyDown(static_cast<ImGuiKey>(this->m_nHkey));
}

void Hotkey::Draw()
{
	ImGui::PushID(this->hotkeyJsonName);
	ImGui::TextUnformatted("Hotkey");
	ImGui::SameLine();
	if (!this->bWaitsInput && ImGui::Button(KeyNames[this->m_nHkey], ImVec2(100.0f, 0.0f)))
		this->bWaitsInput = true;
	else if (this->bWaitsInput)
		ImGui::Button("...", ImVec2(100.0f, 0.0f));
	if (this->bWaitsInput)
		this->Rebind();
	ImGui::PopID();
}

void Hotkey::Rebind()
{
	lastInputTime = std::chrono::steady_clock::now();
	if (this->bWaitsInput && KeyBind::SetToPressedKey(&this->m_nHkey, this->hotkeyJsonName)) {
		this->bWaitsInput = false;
	}
}

