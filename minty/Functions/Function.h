#pragma once

#include <string>

#include "../GUI/Translations.h"

class FN {
public:
	std::string groupName;
	
	virtual std::string getModule() {
		return "Nothing";
	};

	virtual void GUI() {};
	virtual void Outer() {};
	virtual void Status() {};
};