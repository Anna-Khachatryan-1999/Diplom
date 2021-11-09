#include <algorithm>
#include <cmath>
#include <vector>
#include "Helper.h"
#include "Calculates.h"

namespace {
    double ctg(double value)
    {
        return (1 / tan(value));
    }

    double arcctg(double value)
    {
        return atan(1 / value);
    }

    double add(double value1, double value2)
    {
        return (value1 + value2);
    }

    double sub(double value1, double value2)
    {
        return (value1 - value2);
    }

    double divi(double value1, double value2)
    {
        return (value1 / value2);
    }

    double mul(double value1, double value2)
    {
        return (value1 * value2);
    }

    void getEndScop(std::list<std::string>& list, std::list<std::string>::iterator& it)
    {
        while (it != list.end()) {
            if (*it == "(") {
                getEndScop( list, ++it);
            }
            if (*it == ")") {
                ++it;
                return;
            }
            ++it;
        }
    }

    void getPreviousScop(std::list<std::string>& list, std::list<std::string>::iterator& it)
    {
        while (true) {
            if (*it == ")") {
                getPreviousScop( list, --it);
            }
            if (*it == "(") {
                if (it != list.begin()) {
                    --it;
                }
                return;
            }
            --it;
        }
    }
}
Calculates* Calculates::m_calculates = nullptr;
std::unordered_map<std::string, std::function<double(double)>> Calculates::m_mapKey = {
    {"cos", cos},
    {"sin", sin},
    {"tg", tan},
    {"ctg", ctg},
    {"arccos", acos},
    {"arcsin", asin},
    {"arctg", atan},
    {"arcctg", arcctg},
    {"ln", log},
    {"log", log10},
    {"sqrt", sqrt},
    {"root", sqrt},
    {"e^", exp},
    {"abs", abs}
};

std::unordered_map<std::string, std::function<double(double, double)>> Calculates::m_mapSign = {
    {"+", add},
    {"-", sub},
    {"*", mul},
    {"/", divi},
    {"^", pow}
};

std::string Calculates::startCalculates(std::list<std::string> items)
{
    return mainCalculates(items);
}

std::string Calculates::mainCalculates(std::list<std::string>& items)
{
    for (auto lit = items.begin(); lit != items.end(); ++lit) {
        if (Helper::isKey(*lit)) {
            std::list<std::string>::iterator bit = lit;
            std::list<std::string>::iterator nit = lit;
            ++++nit;
            getEndScop(items, nit);
            std::list<std::string> list(++bit, nit);
            *lit = calculatesKey(*lit, list);
            items.erase(bit, nit);
        }
    }
    findAndCalculate(items, "^");
    findAndCalculate(items, "*");
    findAndCalculate(items, "/");
    findAndCalculate(items, "-");
    findAndCalculate(items, "+");
    if (items.size() > 1) {

    }
    return *items.begin();
}

void Calculates::findeBNIters(std::list<std::string>& items,
                            const std::list<std::string>::iterator& it,
                            std::list<std::string>::iterator& bit,
                            std::list<std::string>::iterator& nit)
{
    auto lit = it;
    --lit;
    if (*lit == ")") {
        getPreviousScop(items, --lit);
        if (*lit != "(") {
            if (!Helper::isKey(*lit)) {
                ++lit;
            }
        }
    }
    bit = lit;

    lit = it;
    ++lit;
    if (Helper::isKey(*lit)) {
        ++lit;
    }
    if (*lit == "(") {
        getEndScop(items, ++lit);
    } else {
        ++lit;
    }
    nit = lit;
}

std::string Calculates::calculatesPower(std::list<std::string>& firstlist,
                                     std::list<std::string>& secondlist,
                                     const std::string& sign)
{
    std::string first;
    std::string second;
    if (firstlist.size() > 1) {
        if (!Helper::isKey(*firstlist.begin())) {
            firstlist.erase(firstlist.begin());
            firstlist.pop_back();
        }
        if (firstlist.size() > 1) {
            first = mainCalculates(firstlist);
        } else {
            first = *firstlist.begin();
        }
    } else {
        first = *firstlist.begin();
    }
    if (secondlist.size() > 1) {
        if (!Helper::isKey(*secondlist.begin())) {
            secondlist.erase(secondlist.begin());
            secondlist.pop_back();
        }
        second = mainCalculates(secondlist);
    } else {
        second = *secondlist.begin();
    }
    return std::to_string(m_mapSign[sign](std::stod(first), std::stod(second)));
}

std::string Calculates::calculatesKey(const std::string& keyName, std::list<std::string>& list)
{
    std::string value;
    list.erase(list.begin());
    list.pop_back();
    if (list.size() > 1) {
        value = mainCalculates(list);
    } else {
        value = *list.begin();
    }
    return std::to_string(m_mapKey[keyName](std::stod(value)));
}

void Calculates::findAndCalculate(std::list<std::string>& items, const std::string& sign)
{
    auto it = std::find(items.begin(), items.end(), sign);
    while (it != items.end()) {
        std::list<std::string>::iterator bit;
        std::list<std::string>::iterator nit;
        findeBNIters(items, it, bit, nit);
        std::list<std::string> firstlist(bit, it);
        std::list<std::string> secondlist(++it, nit);
        --it;
        *bit = calculatesPower(firstlist, secondlist, sign);
        ++bit;
        items.erase(bit, nit);
        it = std::find(items.begin(), items.end(), sign);
    }

}
