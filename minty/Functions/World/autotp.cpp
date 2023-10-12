#include "autotp.h"

namespace cheat {
    std::vector<AutoTP::TP> AutoTP::parseds;
    std::atomic<bool> stopThread(false);

    void TeleportToCurrentPoint(int point) {
        if (point >= 0 && point < AutoTP::parseds.size()) {
            AutoTP::currentPoint = AutoTP::parseds[point];
            util::log(M_Info, "Teleporting to point: %s", AutoTP::parseds[point].name.c_str());

            app::ActorUtils_SetAvatarPos(AutoTP::parseds[point].position);

            util::log(M_Info, "Teleported to pos: %f, %f, %f", AutoTP::currentPoint.position.x, AutoTP::currentPoint.position.y, AutoTP::currentPoint.position.z);
        }
    }

    void AutoTpThread() {
        while (!stopThread.load()) {
            if (AutoTP::ifAutoTP && AutoTP::b_startTeleporting) {
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

    void AutoTP::Status() {}

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

    AutoTP::AutoTP() {
        std::thread thread(AutoTpThread);
        thread.detach();
    }

    void AutoTP::GUI() {
        ImGui::Checkbox("Auto TP", &ifAutoTP);
        if (ifAutoTP) {
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
}