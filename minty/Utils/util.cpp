#include "util.h"


namespace util {
	std::vector<std::string> split(const std::string& content, const std::string& delimiter) {
		std::vector<std::string> tokens;
		size_t pos = 0;
		size_t prevPos = 0;
		std::string token;

		while ((pos = content.find(delimiter, prevPos)) != std::string::npos) {
			token = content.substr(prevPos, pos - prevPos);
			tokens.push_back(token);
			prevPos = pos + delimiter.length();
		}

		tokens.push_back(content.substr(prevPos));
		return tokens;
	}
	int64_t GetCurrentTimeMillisec()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
}
