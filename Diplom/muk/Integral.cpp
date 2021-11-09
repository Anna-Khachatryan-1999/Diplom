#include "Integral.h"
#include "Parser.h"
#include "Calculates.h"
#include "Optimization.h"
#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm>

Integral::Integral(std::string function) {
    if ((function.size() == 1) && (Helper::isNumber(function))) {
        function = "x_123";
    }
    Parser* parser = Parser::getParser();
    Optimization* optimization_item = Optimization::getOptimization();
    std::list<std::string> words;
    if (!parser->parse(function, words)) {
        throw(InvalidParse());
        m_invalidPars = true;
    } else {
        optimization_item->startOptimization(words, m_items);
        m_mainitems.insert(m_mainitems.end(), m_items.begin(), m_items.end());
        m_invalidPars = false;;
    }
}

void Integral::getVariables(std::list<std::string>& variables) const
{
    getVariables(m_mainitems, variables);
}

void Integral::getVariables(const std::list<std::string>& list, std::list<std::string>& variables) const
{
    variables.clear();
    for (const auto& litem : list) {
        if(Helper::isVariable(litem)) {
            auto find = std::find(variables.begin(), variables.end(), litem);
            if (find != variables.end()) {
                continue;
            }
            variables.push_back(litem);
        }
    }
}

void Integral::variablesReplacementOfNumbers(std::list<BufForIntegral> pairs) {
    for (auto& current_pair : pairs) {
            if (current_pair.getVariableName() == "&") {
                std::replace(m_items.begin(), m_items.end(), current_pair.getVariableName(), std::to_string(M_PI));
            } else {
             std::replace(m_items.begin(), m_items.end(), current_pair.getVariableName(), current_pair.getDoubleValue());
            }
    }
}

double Integral::calculates(const std::string& integralVariables, double value)
{
    Calculates* cal = Calculates::getCalculates();
    std::list<std::string> list(m_items.begin(), m_items.end());
    std::replace(list.begin(), list.end(), integralVariables, std::to_string(value));
    return std::stod(cal->startCalculates(list));
}

void Integral::print()
{
    for (const auto& litem : m_items) {
        std::cout << litem << " ";
    }
    std::cout << std::endl;
}

double Integral::Function(std::list<BufForIntegral> pairs, std::string variables, double value)
{
    variablesReplacementOfNumbers(pairs);
    return calculates(variables, value);
}

std::string Integral::integralFunction() const
{
    std::string str = "";
    for (const auto& litem : m_items) {
        str += litem;
    }
    return str;
}

void Integral::unrealIntegralsInfiniteAndInfinite(std::string& variables)
{
    std::list<std::string> list = {"(", "t", "/" , "(", "1", "-", "t", "^", "2", ")", ")"};
     for (auto it = m_items.begin() ; it != m_items.end() ; ++it) {
        if (*it == variables) {
            it = m_items.erase(it);
            m_items.insert(it, list.begin(), list.end());
        }
     }
    list.clear();
    list = {"(", "(", "1", "+", "t", "^", "2", ")", "/" , "(", "1", "-", "t", "^", "2", ")", "^", "2", ")", "*", "("};
    m_items.insert(m_items.begin(), list.begin(), list.end());
    m_items.push_back(")");
    Optimization* optimization_item = Optimization::getOptimization();
    std::list<std::string> str;
    str.insert (str.begin(),m_items.begin(), m_items.end());
    m_items.clear();
    optimization_item->startOptimization(str, m_items);
    variables = "t";
}

void Integral::unrealIntegralsInfiniteAndNumber(std::string& variables, double end)
{
    std::list<std::string> list = {"(",std::to_string(end), "-", "(", "1", "-", "t", ")", "/" , "t",  ")"};
    for (auto it = m_items.begin() ; it != m_items.end() ; ++it) {
        if (*it == variables) {
            it = m_items.erase(it);
            m_items.insert(it, list.begin(), list.end());
        }
    }
    list.clear();
    list = {"(", "1", "/", "t", "^", "2", ")", "*", "("};
    m_items.insert(m_items.begin(), list.begin(), list.end());
    m_items.push_back(")");
    Optimization* optimization_item = Optimization::getOptimization();
    std::list<std::string> str;
    str.insert (str.begin(),m_items.begin(), m_items.end());
    m_items.clear();
    optimization_item->startOptimization(str, m_items);
    variables = "t";
}

void Integral::unrealIntegralsNumberAndInfinite(std::string& variables,double begin)
{
    std::list<std::string> list = {"(",std::to_string(begin), "+" "t", "/" , "(", "1", "-", "t", ")", ")"};
     for (auto it = m_items.begin() ; it != m_items.end() ; ++it) {
        if (*it == variables) {
            it = m_items.erase(it);
            m_items.insert(it, list.begin(), list.end());
        }
     }
    list.clear();
    list = {"(", "1", "/", "(", "1", "-", "t", ")", "^", "2", ")", "*", "("};
    m_items.insert(m_items.begin(), list.begin(), list.end());
    m_items.push_back(")");
    print();
    Optimization* optimization_item = Optimization::getOptimization();
     std::list<std::string> str;
        str.insert (str.begin(),m_items.begin(), m_items.end());
        m_items.clear();
    optimization_item->startOptimization(str, m_items);
    variables = "t";
    print();

}

double Integral::integralMetodLeftRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    if (begin == (-std::numeric_limits<int>::max())) {
        if (end == std::numeric_limits<int>::max()) {
            unrealIntegralsInfiniteAndInfinite(variables);
            begin = -1;
        } else {
        unrealIntegralsInfiniteAndNumber(variables, end);
            begin = 0;
        }
        end = 1;
    } else if (end == std::numeric_limits<int>::max()) {
            unrealIntegralsNumberAndInfinite(variables, begin);
    //print();
        begin = 0;
        end = 1;
    }
    //print();
    double h = (end - begin) / size;
    double value = begin;
    double number = calculates(variables, begin);
    while ((size--) > 1) {
        value += h;
        number += calculates(variables, value);
    }
    return h * number;
}

double Integral::integralMetodRightRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) / size;
    double value = end;
    double number = calculates(variables, begin);
    while ((size--) > 1) {
        value -= h;
        number += calculates(variables, value);
    }
    return h * number;
}

double Integral::integralMetodAverageRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) / size;
    double value = begin + h/2;
    double number = calculates(variables, value);
    while ((size--) > 1) {
        value += h;
        number += calculates(variables, value);
    }
    return h * number;
}

double Integral::integralMetodTables(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) / size;
    double value = begin;
    double number = (calculates(variables, begin) + calculates(variables, end)) / 2;
    while ((size--) > 1) {
        value += h;
        number += calculates(variables, value);
    }
    return h * number;
}

double Integral::integralMetodSimpson(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) / (2 * size);
    double value1 = begin;
    double value2;
    double number = calculates(variables, begin) + calculates(variables, end);
    for (int i = 1; i < size; i++) {
        value2 = value1 + h;
        value1 = value2 + h;
        number += ((4 * calculates(variables, value2)) + (2 * calculates(variables, value1)));
    }
    if (size > 1) {
        value2 = value1 + h;
        number += (4 * calculates(variables, value2));
    }
    return h/3 * number;
}

double Integral::integralMetodSimpsonThreeEighths(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) /  size;
    double value = begin;
    double number = calculates(variables, begin) + calculates(variables, end);
    for (int i = 1; i < size; i ++) {
        value += h;
        if (i % 3 == 0) {
            number += 2 * calculates(variables, value);
        } else {
            number += 3 * calculates(variables, value);
        }
    }
    return 3* h * number /  8;
}

double Integral::integralMetodBoole(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) /  size;
    double value = begin + h;
    double number = 7 * (calculates(variables, begin) + calculates(variables, end));
     for (int i = 1; i < size; i += 2) {
        value += 2 * h;
        number += 32 * calculates(variables, value);
     }
    value = begin + 2 * h;
    for (int i = 2; i < size; i += 4) {
        number += 12 * calculates(variables, value);
        value += 4 * h;
    }
    value = begin + 4 * h;
    for (int i = 4; i < size; i += 4) {
        number += 14 * calculates(variables, value);
        value += 4 * h;
    }
    return (2 * h / 45) * number;
}

double Integral::integralMetodWeddles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size)
{
    variablesReplacementOfNumbers(pairs);
    double h = (end - begin) /  size;
    double value = begin;
    double number = calculates(variables, begin) + calculates(variables, end);
    for (int i = 1; i < size; i ++) {
        value += h;
        if (i % 2 == 0) {
            if (i % 3 == 0) {
                number += 2 * calculates(variables, value);
            } else {
                number += calculates(variables, value);
            }
        } else if (i % 3 == 0) {
            number += 6 * calculates(variables, value);
        } else {
            number += 5 * calculates(variables, value);
        }
    }
    return 3* h * number /  10;
}

void Integral::updateFunction()
{
    m_items.clear();
    m_items.insert(m_items.end(), m_mainitems.begin(), m_mainitems.end());
}
