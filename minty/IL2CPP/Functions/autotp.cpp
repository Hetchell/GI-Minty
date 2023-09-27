#include "autotp.h"

static bool ifAutoTP;
static bool ifAutomatic;
static bool ifManual;
static char folderpathBuf[1024] = "";
static float timerWait;

app::Vector3 parsedPos;
std::string parsedName;
std::string parsedDesc;

std::vector<il2fns::autotp::TP> parseds;

int currPos;
int allPos;

namespace il2fns {
	namespace autotp {
		HANDLE autoTpThread();
		void GUI() {
			ImGui::Checkbox("Auto TP", &ifAutoTP);
			if (ifAutoTP) {
				ImGui::InputText("Json folder", folderpathBuf, sizeof(folderpathBuf));
				if (ImGui::Button("Read jsons")) {
					std::ifstream stream;
					stream.open(folderpathBuf);
					nlohmann::json parsed = nlohmann::json::parse(stream);

					try {
						TP tp;
						tp.name = parsed["name"];
						tp.desc = parsed["description"];
						tp.pos = { parsed["position"][0], parsed["position"][1] , parsed["position"][2] };
						parseds.push_back(tp);
					}
					catch (nlohmann::json::exception e) {
						std::cout << e.what() << std::endl;
					}
				}
				if (!parseds.empty()) {
					util::log(M_Info, "name: %s", parseds.back().name);
					util::log(M_Info, "desc: %S", parseds.back().desc);
					ImGui::Text("Files found: %i", 5);
					ImGui::Separator();
					ImGui::Text("Current point name: %s", parseds.back().name);
					ImGui::Text("Current point description: %s", parseds.back().desc);
					ImGui::Text("Current point pos: %f, %f, %f", parseds.back().pos.x, parseds.back().pos.y, parseds.back().pos.z);
					ImGui::Separator();
					ImGui::Checkbox("TP automatically through all points", &ifAutomatic);
					if (ifAutomatic) {
						ImGui::SliderFloat("Time to wait", &timerWait, 1, 100);
						autoTpThread();
					}
					ImGui::Separator();
					ImGui::Checkbox("TP manually", &ifManual);
					if (ifManual) {
						if (ImGui::Button("<")) {
							if (currPos < allPos) {
								currPos--;
							}
						}

						if (ImGui::Button(">")) {
							if (currPos < allPos) {
								currPos++;
							}
						}
					}
				}
			}
		}

		HANDLE autoTpThread() {
			if (ifAutoTP && ifAutomatic) {
				//app::ActorUtiils_SetAvatarPos(parsedPos);
				Sleep(timerWait);
			}
			return 0;
		}
	}
}