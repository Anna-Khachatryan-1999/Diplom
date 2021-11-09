#pragma once

#include <string>
#include <list>

class Parser
{
private:
    Parser() = default;
    ~Parser() = default;

public:
    static Parser* getParser();

public:
    bool parse(std::string line, std::list<std::string>& words);

private:
    int findeSign(const std::string& key, const std::string& line);
    void min(int& first, int second);
    int findeFirstSign(const std::string& str);
    int findeKey(const std::string key, const std::string& line, int& lenght);
    void min(int& first, int second, int& lfirst, int lsecond);
    int findeFirstKey(const std::string& str, int& lenght);
    int findeFirstKeyOrSign(const std::string& line, int& lenght);
    void ParseLineIntoWords(std::string line, std::list<std::string>& words);

    void parsePower(std::list<std::string>& words, std::list<std::string>::iterator& it);
    void insert_after(std::list<std::string>& list, std::list<std::string>::iterator& it, std::string value);
    void parsAfterScop(std::list<std::string>& words, std::list<std::string>::iterator& it);
    void parseKey(std::list<std::string>& words, std::list<std::string>::iterator& it);
    void addMultiplicationSign(std::list<std::string>& words, std::list<std::string>::iterator& it);
    void parseOpenScop(std::list<std::string>& words);
    void parseCloseScop(std::list<std::string>& words);
    void parseGrups(std::list<std::string>& words, std::list<std::string>::iterator& it, bool isscop = false);
    void parseStrtoStrandNumber(std::string str, std::string& str1, std::string& number);
    void parseStrToStrAndVariable(std::string str, std::string& str1, std::string& variable);
    void parseLineVariableNumber (std::list<std::string>& words, std::list<std::string>::iterator& it, bool key = false);
    //void optScop(std::list<std::string>& words, std::list<std::string>::const_iterator& it);
    //void optSign(std::list<std::string>& words, std::list<std::string>::const_iterator& it);
    //void optimizationToWords(std::list<std::string>& words);

    //find incorect sitax

    bool checkErrors(const std::list<std::string>& list);

    bool checkValue(const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkSign (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkOScop (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkCScop (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkKey  (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkScop (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);
    bool checkE  (const std::list<std::string>& list, std::list<std::string>::const_iterator& it);


private:
    static Parser *s_parser;
};
