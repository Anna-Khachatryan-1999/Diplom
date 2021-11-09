#include <string>
#include <list>
#include <functional>
#include <unordered_map>

class Calculates
{
private:
    Calculates() = default;
    ~Calculates() = default;

public:
    std::string startCalculates(std::list<std::string> items);

public:
    static Calculates* getCalculates();

private:
    std::string mainCalculates(std::list<std::string>& items);
    void findeBNIters(std::list<std::string>& items, const std::list<std::string>::iterator& it,
            std::list<std::string>::iterator& bit, std::list<std::string>::iterator& nit);
    std::string calculatesPower(std::list<std::string>& firstlist, std::list<std::string>& secondlist, const std::string& sign);
    std::string calculatesKey(const std::string& keyName, std::list<std::string>& list);

    void findAndCalculate(std::list<std::string>& items, const std::string& sign);

private:
    static Calculates* m_calculates;
    static  std::unordered_map<std::string, std::function<double(double)>> m_mapKey;
    static  std::unordered_map<std::string, std::function<double(double, double)>> m_mapSign;
};


inline Calculates* Calculates::getCalculates()
{
    if (m_calculates == nullptr) {
        m_calculates = new Calculates();
    }
    return m_calculates;
}
