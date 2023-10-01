#pragma once

#include <string>
#include "../GUI/Translations.h"

class FN {
public:
	std::string groupName;
	
	virtual void GUI() {};
	virtual void Outer() {};
	virtual void Status() {};

	virtual std::string GetGroupName() {
		return "groupName";
	};
};