#include "Hotkey.h"

Hotkey::Hotkey() {
	this->key = -1;
	this->path = "";
	this->name = "";
	this->waitInput = false;
}

Hotkey::Hotkey(const char* path) {
	this->key = config::getValue(path, "hotkey", -1).getValue();
	this->path = path;
	this->name = "hotkey";
	this->waitInput = false;
}

Hotkey::Hotkey(const char* path, short key) {
	this->key = config::getValue(path, "hotkey", key).getValue();
	this->path = path;
	this->name = "hotkey";
	this->waitInput = false;
}

Hotkey::Hotkey(const char* path, const char* name) {
	this->key = config::getValue(path, name, -1).getValue();
	this->path = path;
	this->name = name;
	this->waitInput = false;
}

Hotkey::Hotkey(const char* path, const char* name, short key) {
	this->key = config::getValue(path, name, key).getValue();
	this->path = path;
	this->name = name;
	this->waitInput = false;
}

bool Hotkey::IsPressed() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastInputTime).count() > 100 &&
		ImGui::IsKeyPressed(static_cast<ImGuiKey>(this->key), false);
}

bool Hotkey::IsDown() {
	return ImGui::IsKeyDown(static_cast<ImGuiKey>(this->key));
}

void Hotkey::Draw() {
	ImGui::PushID(this->path);
	ImGui::TextUnformatted("Hotkey");
	ImGui::SameLine();

	if (!this->waitInput && ImGui::Button(KeyBind::getKeyName(this->key).c_str(), ImVec2(100.0f, 0.0f)))
		this->waitInput = true;
	else if (this->waitInput)
		ImGui::Button("...", ImVec2(100.0f, 0.0f));

	if (this->waitInput)
		this->Rebind();
	ImGui::PopID();
}

void Hotkey::Draw(const char* label) {
	ImGui::PushID(this->path);
	ImGui::TextUnformatted(label);
	ImGui::SameLine();

	if (!this->waitInput && ImGui::Button(KeyBind::getKeyName(this->key).c_str(), ImVec2(100.0f, 0.0f)))
		this->waitInput = true;
	else if (this->waitInput)
		ImGui::Button("...", ImVec2(100.0f, 0.0f));

	if (this->waitInput)
		this->Rebind();
	ImGui::PopID();
}

void Hotkey::Rebind() {
	lastInputTime = std::chrono::steady_clock::now();

	if (this->waitInput && KeyBind::SetToPressedKey(this->path, this->name, &this->key))
		this->waitInput = false;
}
