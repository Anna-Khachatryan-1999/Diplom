#pragma once
#include <string>

class Helper
{
private:
    Helper() = default;
    ~Helper() = default;
public:
    static bool isKey(const std::string& str);
    static bool isSign(const std::string& str);
    static bool isNumber(const std::string& str);
    static bool isNumberZ(const std::string& str);
    static bool isLetter(const std::string& str);
    static bool isValue(const std::string& str);
    static bool isVariable(const std::string& str);
    static bool haveNumber(const std::string& str);
};
