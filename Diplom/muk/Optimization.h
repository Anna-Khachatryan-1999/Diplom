#include <list>
#include <string>

enum class SIGN : unsigned char {PLUS, MINUS};
class OptimizationItem
{
public:
    OptimizationItem(SIGN sign, const std::list<std::string>& list) :
        m_sign(sign), m_list(list) {}
    ~OptimizationItem() = default;

public:
    SIGN getSign() {return m_sign;}
    void setSign(SIGN sign) {m_sign = sign;}
    std::list<std::string>& getList() {return m_list;}
    const std::list<std::string>& getConstList() const {return m_list;}
private:
    SIGN m_sign;
    std::list<std::string> m_list;
};


class Optimization
{
private:
    Optimization() = default;
    ~Optimization() = default;

public:
    static Optimization* getOptimization();

public:
    void startOptimization(const std::list<std::string>& list, std::list<OptimizationItem>& items);
    void startOptimization(const std::list<std::string>& list, std::list<std::string>& items);
   // void print();

private:
    void parseforOptimization(const std::list<std::string>& list,
            std::list<OptimizationItem>& item);

    void parseforOptimization(OptimizationItem& opt, std::list<OptimizationItem>& item);
    void removScop(std::list<OptimizationItem>& optList, std::list<OptimizationItem>::iterator&  it);
    void changeSignForPower(std::list<std::string>& list, std::list<std::string>::iterator& it);
    void nextSign(std::list<std::string>& list, std::list<std::string>::iterator& it);
    bool isParsList(std::list<std::string>& list);
    bool removScopCore(OptimizationItem& opt);
    void parsePower(std::list<std::string>& list, std::list<std::string>::iterator&  it, std::list<OptimizationItem>::iterator& vit);
    void parsePreviousScop(std::list<std::string>& list, std::list<std::string>::iterator it, std::list<OptimizationItem>::iterator& vit);
    void parseNextScop(std::list<std::string>& list, std::list<std::string>::iterator& it, std::list<OptimizationItem>::iterator& vit);
    void parseNextScopCore(std::list<std::string>& list, std::list<std::string>::iterator nit, std::list<std::string>::iterator it,
            std::list<OptimizationItem>::iterator& vit, std::list<OptimizationItem>& item);

    void removUselessScop();

private:
    static Optimization* m_optimization;
    std::list<OptimizationItem> m_items;
};


