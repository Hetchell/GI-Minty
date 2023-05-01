#pragma once

#include <sstream>
#include <string>

template<typename T>
const char* get_ptr(const T& value) {
    std::ostringstream oss;
    oss << value;
    std::string str = oss.str();
    if (str.empty()) {
        return "nullptr";
    }
    return str.c_str();
}