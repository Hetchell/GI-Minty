#pragma once

#include <string>
#include "../GUI/Translations.h"

class FN {
public:
	virtual std::string groupName() {
		return "NOPE";
	}

	virtual void GUI() {};
	virtual void Outer() {};
	virtual void Status() {};
};