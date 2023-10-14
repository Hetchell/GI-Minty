#pragma once

#include <string>

template <typename T>
class ConfigField {
private:
	std::string path;
	std::string key;
	T value;
public:
	explicit ConfigField() {}

	explicit ConfigField(const std::string path, const std::string key, const T value) {
		this->path = path;
		this->key = key;
		this->value = value;
	}

	std::string getPath() {
		return this->path;
	}

	std::string getKey() {
		return this->key;
	}

	T& getValue() {
		return this->value;
	}

	void setValue(T value) {
		this->value = value;
	}
};
