#pragma once

#include <string>

#include "../GUI/Translations.h"

class Function {
public:
	virtual std::string getModule() {
		return "Nothing";
	};

	virtual void GUI() {};
	virtual void Outer() {};
	virtual void Status() {};
};
