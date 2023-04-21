#include "json.hpp"
#include <iostream>
#include <fstream>


std::filesystem::path settings_path = std::filesystem::current_path() / "minty";
std::ofstream settings_fileO(settings_path);
std::ifstream settings_fileI(settings_path);

bool writeToJsonConfig(std::string filename, nlohmann::json jsonObject) {
	// Write the updated JSON object to file
	std::ifstream config_file(filename);
	nlohmann::json config_json;
	if (config_file.is_open()) {
		config_file >> config_json;
		config_file.close();
	}
	else {
		return false;
	}

	config_json.merge_patch(jsonObject);
	std::ofstream merged_file(filename);
	if (merged_file.is_open()) {
		merged_file << config_json.dump(4); // pretty-print with 4 spaces
		merged_file.close();
		return true;
	}
	else {
		return false;
	}
}