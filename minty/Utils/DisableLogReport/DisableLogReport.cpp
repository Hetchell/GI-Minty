#include "DisableLogReport.h"

void DisableLogReport() {
	char szProcessPath[MAX_PATH]{};
	GetModuleFileNameA(nullptr, szProcessPath, MAX_PATH);

	auto path = std::filesystem::path(szProcessPath);
	auto ProcessName = path.filename().string();
	ProcessName = ProcessName.substr(0, ProcessName.find_last_of('.'));

	auto Astrolabe = path.parent_path() / (ProcessName + "_Data\\Plugins\\Astrolabe.dll");
	auto MiHoYoMTRSDK = path.parent_path() / (ProcessName + "_Data\\Plugins\\MiHoYoMTRSDK.dll");
	//auto Telemetry = path.parent_path() / (ProcessName + "_Data\\Plugins\\telemetry.dll");

	// open exclusive access to these two dlls
	// so they cannot be loaded
	CreateFileA(Astrolabe.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	CreateFileA(MiHoYoMTRSDK.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	//CreateFileA(Telemetry.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	//хз € канеш не разбираюсь но можно ли просто закрыть хэндл telemetry.dll или что то типа того не удал€€ сам файл?????
}