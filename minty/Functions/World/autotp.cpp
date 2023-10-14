#include "AutoTP.h"

namespace cheat {
    std::vector<AutoTP::TP> AutoTP::parseds;
    std::atomic<bool> stopThread(false);

    static void TeleportToCurrentPoint(int point);
    static void AutoTpThread();

    AutoTP::AutoTP() {
        f_Enabled = config::getValue("functions:AutoTP", "enabled", false);

        std::thread thread(AutoTpThread);
        thread.detach();
    }

    AutoTP& AutoTP::getInstance() {
        static AutoTP instance;
        return instance;
    }

    void AutoTP::GUI() {
        ConfigCheckbox("Auto TP", f_Enabled);

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            ImGui::InputText("Json folder", folderPathBuffer, sizeof(folderPathBuffer));

            if (ImGui::Button("Read jsons")) {
                parseds.clear();
                std::string folderPath = folderPathBuffer;
                if (!std::filesystem::exists(folderPath)) {
                    std::filesystem::path path = std::filesystem::current_path() / folderPath;
                    folderPath = path.string();
                    if (!std::filesystem::exists(path)) {
                        util::log(M_Error, "Folder not found: %s", folderPath); // Use %s for string format
                        return;
                    }
                }
                for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".json") {
                        std::ifstream stream(entry.path());
                        if (stream.good()) {
                            nlohmann::json parsed;
                            try {
                                stream >> parsed;
                                TP tp;
                                tp.name = parsed["name"];
                                tp.description = parsed["description"];
                                tp.position = { parsed["position"][0], parsed["position"][1], parsed["position"][2] };
                                parseds.push_back(tp);
                            }
                            catch (const nlohmann::json::exception& e) {
                                std::cout << e.what() << std::endl;
                            }
                        }
                        else {
                            std::cout << "Failed to open file: " << entry.path() << std::endl;
                        }
                    }
                }
            }

            if (!parseds.empty()) {
                ImGui::Text("Amount of loaded points: %zu", parseds.size());
                ImGui::Separator();
                ImGui::Text("Current point name: %s", currentPoint.name.c_str());
                ImGui::Text("Current point description: %s", currentPoint.description.c_str());
                ImGui::Text("Current point pos: %f, %f, %f", currentPoint.position.x, currentPoint.position.y, currentPoint.position.z);
                ImGui::Separator();
                ImGui::Checkbox("TP automatically through all points", &ifAutomatic);

                if (ifAutomatic) {
                    if (!b_startTeleporting) {
                        if (ImGui::Button("Start teleporting")) {
                            b_startTeleporting = true;
                            util::log(M_Debug, "Start teleporting pressed");
                        }
                    }
                    if (b_startTeleporting) {
                        if (ImGui::Button("Stop teleporting")) {
                            b_startTeleporting = false;
                            util::log(M_Debug, "Stop teleporting pressed");
                        }
                    }
                    ImGui::SliderFloat("Time to wait", &timerWait, 0.f, 100.0f);
                    autoTeleportHotkey.Draw();
                }

                ImGui::Checkbox("TP manually", &ifManual);
                if (ifManual) {
                    ImGui::Text("Manual TP Controls:");
                    ImGui::SameLine();
                    if (ImGui::Button("<")) {
                        if (currentPointIndex > 0) {
                            currentPointIndex--;
                            TeleportToCurrentPoint(currentPointIndex);
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(">")) {
                        if (currentPointIndex < parseds.size() - 1) {
                            currentPointIndex++;
                            TeleportToCurrentPoint(currentPointIndex);
                        }
                    }
                    teleportForwardHotkey.Draw();
                    ImGui::SameLine();
                    teleportBackHotkey.Draw();
                }
                ImGui::Separator();
            }
            ImGui::Unindent();
        }
    }

    void AutoTP::Outer() {
        if (teleportBackHotkey.IsPressed()) {
            if (currentPointIndex > 0) {
                currentPointIndex--;
                TeleportToCurrentPoint(currentPointIndex);
            }
        }
        if (teleportForwardHotkey.IsPressed()) {
            if (currentPointIndex < parseds.size() - 1) {
                currentPointIndex++;
                TeleportToCurrentPoint(currentPointIndex);
            }
        }
        if (autoTeleportHotkey.IsPressed())
            b_startTeleporting = !b_startTeleporting;
    }

    void AutoTP::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("AutoTP");
    }

    std::string AutoTP::getModule() {
        return _("World");
    }

    void TeleportToCurrentPoint(int point) {
        if (point >= 0 && point < AutoTP::parseds.size()) {
            AutoTP::currentPoint = AutoTP::parseds[point];
            util::log(M_Info, "Teleporting to point: %s", AutoTP::parseds[point].name.c_str());
            auto avatarPos = app::MoleMole__ActorUtils__GetAvatarPos();
            auto endPos = AutoTP::parseds[point].position;
            std::thread interpolate([avatarPos, endPos]() {
                    float t = 0.0f;
                    app::Vector3 zero = { 0,0,0 };
                    auto newPos = zero;
                    while (t < 1.0f) {
                        newPos = app::Vector3_Slerp(avatarPos, endPos, t);
                        app::ActorUtils_SetAvatarPos(newPos);
                        t += 5 / 100.0f;
                        util::log(M_Info, "time; %f", t);
                        Sleep(10);
                    } });
            interpolate.detach();
            util::log(M_Info, "Teleported to pos: %f, %f, %f", AutoTP::currentPoint.position.x, AutoTP::currentPoint.position.y, AutoTP::currentPoint.position.z);
        }
    }

    void AutoTpThread() {
        auto& AutoTP = AutoTP::getInstance();

        while (!stopThread.load()) {
            if (!AutoTP.f_Enabled.getValue() || !AutoTP::b_startTeleporting)
                return;

            for (int i = 0; i < AutoTP::parseds.size(); i++) {
                if (!AutoTP::b_startTeleporting)
                    break;

                TeleportToCurrentPoint(i);

                if (AutoTP::parseds.size() - i != 1) {
                    Sleep(static_cast<DWORD>(AutoTP::timerWait * 1000));
                }
            }
            AutoTP::b_startTeleporting = false;
        }
    }
}
