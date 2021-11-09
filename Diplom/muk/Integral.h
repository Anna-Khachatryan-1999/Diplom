#pragma once

#include "Helper.h"
#include <string>
#include <list>

class BufForIntegral
{
public:
    BufForIntegral() = default;
    ~BufForIntegral() = default;
public:
    std::string getDoubleValue() const;
    std::string getVariableName() const;
    bool setDoubleValue(std::string doubleValue);
    bool setVariableName(std::string variableName);

public:
    std::string m_doubleValue;
    std::string m_variableName;
};

//////////////////////
class Integral
{
public:
    Integral(std::string function);
    ~Integral() = default;

public:
    void getVariables(std::list<std::string>& variables) const;
    double Function(std::list<BufForIntegral> pairs, std::string variables, double value);
    std::string integralFunction() const;
    bool isInvalidParse() const;
    void unrealIntegralsInfiniteAndInfinite(std::string& variables);
    void unrealIntegralsInfiniteAndNumber(std::string& variables, double end);
    void unrealIntegralsNumberAndInfinite(std::string& variables, double begin);
    double integralMetodLeftRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodRightRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodAverageRectangles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodTables(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodSimpson(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodSimpsonThreeEighths(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodBoole(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    double integralMetodWeddles(std::list<BufForIntegral> pairs, std::string variables, double begin, double end, int size);
    void updateFunction();

    void print();
public:
    class InvalidParse{};

private:
    double calculates(const std::string& integralVariables, double value);
    void getVariables(const std::list<std::string>& list, std::list<std::string>& variables) const;
    void variablesReplacementOfNumbers(std::list<BufForIntegral> pairs);

private:
    bool m_invalidPars;
    std::list<std::string> m_items;
    std::list<std::string> m_mainitems;
};

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
inline bool Integral::isInvalidParse() const
{
    return m_invalidPars;
}

inline std::string BufForIntegral::getDoubleValue() const
{
    return m_doubleValue;
}

inline std::string BufForIntegral::getVariableName() const
{
    return m_variableName;
}

inline bool BufForIntegral::setDoubleValue(std::string doubleValue)
{
    if(Helper::isNumber(doubleValue)) {
        m_doubleValue = doubleValue;
        return true;
    }
    return false;
}

inline bool BufForIntegral::setVariableName(std::string variableName)
{
    if(Helper::isVariable(variableName)) {
        m_variableName = variableName;
        return true;
    }
    return false;
}


