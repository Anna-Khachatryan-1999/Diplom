#include "Optimization.h"
#include "Helper.h"
#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    void getEndScop(const std::list<std::string>& list, std::list<std::string>::const_iterator& it)
    {
        while (it != list.cend()) {
            if (*it == "(") {
                getEndScop( list, ++it);
                if (it == list.cend()) {
                    throw (0);
                }
            }
            if (*it == ")") {
                ++it;
                return;
            }
            ++it;
        }
    }

    void getEndScop(std::list<std::string>& list, std::list<std::string>::iterator& it)
    {
        while (it != list.end()) {
            if (*it == "(") {
                getEndScop( list, ++it);
                if (it == list.end()) {
                    throw (0);
                }
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

    bool isPreviousScop(std::list<std::string>& list, std::list<std::string>::iterator it)
    {
        if (*it != ")") {
            return false;
        }
        getPreviousScop(list, --it);
        if (*it == "/") {
            return isPreviousScop(list, it);
        }
        if (Helper::isKey(*it )) {
            return false;
        }
        return true;
    }
}
Optimization* Optimization::m_optimization = nullptr;

Optimization* Optimization::getOptimization()
{
    if (m_optimization == nullptr) {
        m_optimization = new Optimization();
    }
    return m_optimization;
}

void getPreviousIterator(std::list<std::string>& list, std::list<std::string>::iterator& it)
{
    if (*it != ")") {
        if (it != list.begin()) {
            if ((*(--it) == "^") || (*it == "/") || (*it == "*")) {
                getPreviousIterator(list, --it);
                return;
            }
        } else {
            return;
        }
    }
    getPreviousScop(list, --it);
    if (it == list.begin()) {
        return;
    }
    if (Helper::isKey(*it)) {
        --it;
    }
    if ((*it == "^") || (*it == "/") || (*it == "*")) {
        getPreviousIterator(list, --it);
    }
    return;
}

void getNextIterator(std::list<std::string>& list, std::list<std::string>::iterator& it)
{
    if (*it != "(") {
        if (++it != list.end()) {
            if ((*it == "^") || (*it == "/")) {
                getNextIterator(list, ++it);
            }
        }
        return;
    }
    if (Helper::isKey(*it)) {
        ++it;
    }
    getEndScop(list, it);
    if (it == list.end())  {
        return;
    }
    if ((*it == "^") || (*it == "/")) {
        getNextIterator(list, ++it);
    }
    return;
}

std::list<std::string>::iterator find(std::list<std::string>::iterator begin,
                                      std::list<std::string>::iterator end,
                                      std::list<std::string>& list,
                                      std::string value)
{
    while (begin != end) {
        if (*begin == value) {
            return begin;
        }
        if (*begin == "(") {
            getEndScop(list, ++begin);
            if (begin == list.end()) {
                return list.end();
            }
            if (*begin == value) {
                return begin;
            }
        }
        ++begin;
    }
    return list.end();
}

void Optimization::parsePreviousScop(std::list<std::string>& list,
                        std::list<std::string>::iterator it,
                        std::list<OptimizationItem>::iterator& vit)
{
    auto bit = it;
    getPreviousIterator(list, --bit);
    auto nit = it;
    auto lnit = it;
    ++lnit;
    getNextIterator(list, ++nit);
    std::list<std::string> blist(bit, it);
    std::list<std::string> nlist(lnit, nit);
    list.insert(bit, nlist.begin(), nlist.end());
    list.erase(bit, it);
    list.insert(lnit, blist.begin(), blist.end());
    list.erase(lnit, nit);
}

void Optimization::parseNextScopCore(std::list<std::string>& list,
                             std::list<std::string>::iterator nit,
                             std::list<std::string>::iterator it,
                             std::list<OptimizationItem>::iterator& vit,
                             std::list<OptimizationItem>& item)
{
    auto bit = it;
    ++++bit;
    auto eit = nit;
    --eit;
    //std::list<std::string> llist(bit, eit);
    OptimizationItem opt(vit->getSign(), std::list<std::string>(bit, eit));
    parseforOptimization(opt, item);
    for (auto el = item.begin() ; el != item.end() ; ++el) {
        std::list<std::string>& lel = (*el).getList();
        auto llit = it;
        getPreviousIterator(list, --llit);
        lel.push_back("*");
        lel.insert(lel.end(), llit, it);
    }
}


void Optimization::parseNextScop(std::list<std::string>& list,
                          std::list<std::string>::iterator& it,
                          std::list<OptimizationItem>::iterator& vit)
{
    auto cvit = vit;
    --cvit;
    bool isbegin = (m_items.begin() == vit);
    auto nit = it;
    ++nit;
    std::list<OptimizationItem> item;
    getEndScop(list, ++nit);
    if (nit == list.end()) {
        parseNextScopCore(list, nit, it, vit, item);

    } else if (*nit == "^") {
        return;
    } else if ((*nit == "*") || (*nit == "/")) {
        parseNextScopCore(list, nit, it, vit, item);
        for (auto it = item.begin(); it != item.end(); ++it) {
            it->getList().insert(it->getList().end(), nit, list.end());
        }
    }
    m_items.insert(vit, item.begin(), item.end());
    m_items.erase(vit);
    if (isbegin) {
        vit = m_items.begin();
        --vit;
    } else {
        vit = cvit;
    }
}

void Optimization::parsePower(std::list<std::string>& list,
                     std::list<std::string>::iterator&  it,
                     std::list<OptimizationItem>::iterator& vit)
{
    auto pit = it;
    --pit;
    auto nit = it;
    ++nit;
    if (isPreviousScop(list, pit) && (*nit == "(")) {
        parseNextScop(list, it, vit);
    } else if (isPreviousScop(list, pit) && (*nit != "(")) {
        parsePreviousScop(list, it, vit);
        parseNextScop(list, it, vit);
    } else if (!isPreviousScop(list, pit) && (*nit == "(")) {
        parseNextScop(list, it, vit);
    } else if (!isPreviousScop(list, pit) && (*nit != "(")) {
        ++it;
        if (it == list.end()) {
            return ;
        }
        it = find(it, list.end(), list, "*");
        if (it == list.end()) {
            return ;
        }
        parsePower(list, it, vit);
    }
}

void Optimization::startOptimization(const std::list<std::string>& list, std::list<std::string>& items)
{
    std::list<OptimizationItem> litems;
    startOptimization(list, litems);
    for(auto it = litems.begin(); it != litems.end(); ++it) {
        if (it->getSign() == SIGN::MINUS) {
            items.push_back("-");
           // items.push_back("(");
            items.insert(items.end(), it->getList().begin(), it->getList().end());
              //  items.push_back(")");
        } else {
            if (it != litems.begin()) {
                items.push_back("+");
            }
          //  items.clear();
            items.insert(items.end(), it->getList().begin(), it->getList().end());
        }
    }
}

void Optimization::startOptimization(const std::list<std::string>& list, std::list<OptimizationItem>& items)
{
    parseforOptimization(list, m_items);
    for(auto it = m_items.begin() ; it != m_items.end() ; ++it) {
        removScop(m_items, it);
    }
    for (auto vit = m_items.begin() ; vit != m_items.end() ; ++vit) {
        std::list<std::string>& item = (*vit).getList();
        std::list<std::string>::iterator it = item.begin();
        it = find(item.begin(), item.end(), item,  "*");
        if (it != item.end()) {
            parsePower(item, it, vit);
        }
    }
    removUselessScop();
    items.clear();
    items.insert(items.end(), m_items.begin(), m_items.end());
    m_items.clear();
}

void Optimization::parseforOptimization(const std::list<std::string>& list, std::list<OptimizationItem>& item)
{
    if (list.empty()) {
        return ;
    }
    auto bit = list.cbegin();
    SIGN sign = SIGN::PLUS;
    if (*bit == "-") {
        sign = SIGN::MINUS;
        ++bit;
    }
    auto it = bit;
    for (; it != list.cend(); ++it) {
        if (*it == "(") {
            getEndScop(list, ++it);
        }
        if (it == list.cend()) {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, list.cend())));
            return;
        }
        if (*it == "+") {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, it)));
            bit = ++it;
            --it;
            sign = SIGN::PLUS;
        }
        if (*it == "-") {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, it)));
            bit = ++it;
            --it;
            sign = SIGN::MINUS;
        }
    }
    item.push_back(OptimizationItem(
                sign, std::list<std::string>(bit, list.cend())));
}

void Optimization::parseforOptimization(OptimizationItem& opt, std::list<OptimizationItem>& item)
{
    std::list<std::string>& list = opt.getList();
    if (list.empty()) {
        return ;
    }
    auto bit = list.cbegin();
    SIGN gsign = opt.getSign();
    SIGN sign = SIGN::PLUS;
    if (*bit == "-") {
        sign = SIGN::MINUS;
        ++bit;
    }
    if (gsign == SIGN::MINUS) {
        sign = ((sign == SIGN::MINUS) ? SIGN::PLUS : SIGN::MINUS);
    }
    auto it = bit;
    for (; it != list.cend(); ++it) {
        if (*it == "(") {
            getEndScop(list, ++it);
        }
        if (it == list.cend()) {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, list.cend())));
            return;
        }
        if (*it == "+") {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, it)));
            bit = ++it;
            --it;
            if (gsign == SIGN::MINUS) {
                sign = SIGN::MINUS;
            } else {
                sign = SIGN::PLUS;
            }
        }
        if (*it == "-") {
            item.push_back(OptimizationItem(
                        sign, std::list<std::string>(bit, it)));
            bit = ++it;
            --it;
            if (gsign == SIGN::MINUS) {
                sign = SIGN::PLUS;
            } else {
                sign = SIGN::MINUS;
            }
        }
    }
    item.push_back(OptimizationItem(
                sign, std::list<std::string>(bit, list.cend())));
}

/*void Optimization::print()
{
    for (auto& vitem : m_items) {
        if (vitem.getSign() == SIGN::PLUS)
        {
            std::cout << "+" <<std::endl;
        } else if (vitem.getSign() == SIGN::MINUS) {
            std::cout << "-" <<std::endl;
        }
        for (const auto& litem : vitem.getList()) {
            std::cout << litem << " ";
        }
        std::cout << std::endl;
    }
}*/
bool Optimization::removScopCore(OptimizationItem& opt)
{
    auto& list = opt.getList();
    auto it = list.begin();
    if (*it == "(") {
        getEndScop(list, ++it);
        if (it == list.end()) {
            list.erase(list.begin());
            --it;
            list.erase(it);
            if (opt.getSign() == SIGN::MINUS) {
            } else if(opt.getSign() == SIGN::PLUS) {
                if (*(list.begin()) == "-") {
                    auto lit = list.begin();
                    ++lit;
                    nextSign(list, lit);
                    if (lit == list.end()) {
                        list.erase(list.begin());
                        opt.setSign(SIGN::MINUS);
                    }
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

void Optimization::removScop(std::list<OptimizationItem>& optList,
        std::list<OptimizationItem>::iterator& it)
{
    auto& list = (*it).getList();
    if (std::find(list.cbegin(), list.cend(), "(") == list.cend()) {
        return;
    }
    while(removScopCore(*it)){}
    if (isParsList(list)) {
        auto lit = it;
        --lit;
        std::list<OptimizationItem> item;
        parseforOptimization(*it, item);
        optList.insert(it, item.begin(), item.end());
        optList.erase(it);
        it = lit;
    }
}

void Optimization::changeSignForPower(std::list<std::string>& list, std::list<std::string>::iterator& it)
{
    if (Helper::isKey(*(++it))) {
        getEndScop(list, ++++it);
    } else if (Helper::isVariable(*it)) {
        ++it;
    } else if (*it == "(") {
        getEndScop(list, ++it);
    }
    list.insert(it, ")");
    list.insert(list.begin(), "(");
    list.insert(list.begin(), "-");
}

void Optimization::nextSign(std::list<std::string>& list, std::list<std::string>::iterator& it)
{
    if (Helper::isValue(*it)) {
        ++it;
        return;
    }
    if (Helper::isKey(*it)) {
        ++it;
        getEndScop(list, ++it);
        return;
    }
    if (*it == "(") {
        getEndScop(list, ++it);
        return;
    }
}

bool Optimization::isParsList(std::list<std::string>& list)
{
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        if (*it == "(") {
            getEndScop(list, ++it);
        }
        if (it == list.cend()) {
            return false;
        }
        if (*it == "+") {
            return true;
        }
        if (*it == "-") {
            return true;
        }
    }
    return false;
}

void Optimization::removUselessScop()
{
    for(auto& item : m_items) {
        std::list<std::string>& list = item.getList();
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            while (*it == "(") {
                ++count;
                ++it;
            }
            while (count > 1) {
                auto eit = it;
                --it;
                getEndScop(list, ++eit);
                if (*eit == ")") {
                    --eit;
                    it = list.erase(it);
                    eit = list.erase(eit);
                }
                --count;
            }
            if (count == 1) {
                count = 0;
            }
        }
    }
}
