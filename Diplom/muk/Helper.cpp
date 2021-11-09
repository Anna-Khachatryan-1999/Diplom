#include "Helper.h"
#include <vector>

bool Helper::isKey(const std::string& str)
{
    static std::vector<std::string> keys = { "cos",
        "sin", "tg", "ctg", "arccos", "arcsin", "arctg",
        "arcctg", "ln", "log", "sqrt", "root", "e^", "abs"};
    for(const auto& item : keys) {
        if(item == str) {
            return true;
        }
    }
    return false;
}

bool Helper::isSign(const std::string& str)
{
    static std::vector<std::string> keys = { "+",
        "-", "*", "/", "^"};
    for(const auto& item : keys) {
        if(item == str) {
            return true;
        }
    }
    return false;
}

bool Helper::isNumber(const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    bool have_point = false;
    for(auto it = str.begin(); it != str.end(); ++it) {
        if((*it < '0' ) || (*it > '9')){
            if ((*it == '.') && (!have_point)) {
                have_point = true;
            } else {
                return false;
            }
        }
    }
    if(str == "."){
        return false;
    }
    return true;
}

bool Helper::isNumberZ(const std::string& str)
{
    std::string str1;
    if (str[0] == '-') {
        str1 = str.substr(1);
    } else {
        str1 = str;
    }
    return isNumber(str1);
}

bool Helper::haveNumber(const std::string& str)
{
    try {
        std::stod(str);
    }
    catch(...) {
        return false;
    }
    return true;
}

bool Helper::isLetter(const std::string& str)
{
    if (str.size() != 1) {
        return false;
    }
    if (("z" >= str) && (str >= "a")) {
        return true;
    }
    return false;
}

bool Helper::isVariable(const std::string& str)
{
    if (str.size() == 1) {
        if (("a" <= str) && ("z" >= str) && ("e" != str)) {
            return true;
        }
        return false;
    }
    if (str.size() == 2) {
        return false;
    }

    bool status = true;
    status &= (('a' <= str[0]) && ('z' >= str[0]));
    status &= ('_' == str[1]);
    int size = str.size();
    for (int i = 2; i < size; ++i) {
        status &= isdigit(str[i]);
    }
    return status;
}

bool Helper::isValue(const std::string& str)
{
    if (isNumber(str)) {
        return true;
    }
    if (isVariable(str)) {
        return true;
    }
    return false;
}
