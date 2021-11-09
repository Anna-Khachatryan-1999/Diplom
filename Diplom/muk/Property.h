#pragma once
#include <QDockWidget>
#include <QString>
#include <vector>
#include <QWidget>
#include <list>

class QStandardItemModel;
class QTableView;
class QStackedLayout;
class QLineEdit;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class BufForIntegral;

class PropertyItem {
public:
    PropertyItem(QString function, QString result, QString algoritm, QString number, QString time) :
        m_function(function), m_result(result), m_algoritm(algoritm), m_number(number), m_time(time) {}

public:
    const QString& function() const {return m_function;}
    const QString& result() const {return m_result;}
    const QString& algoritm() const {return m_algoritm;}
    const QString& number() const {return m_number;}
    const QString& time() const {return m_time;}

private:
    QString m_function;
    QString m_result;
    QString m_algoritm;
    QString m_number;
    QString m_time;
};

class Property : public QDockWidget
{
private:
    Property(const QString& title, QWidget* parent = nullptr);

public:
    static void creatProperty(const QString& title, QWidget* parent = nullptr);
    static Property* getProperty();
    void addItem(const PropertyItem& Property_items);

private:
    QStackedLayout* m_layout;
    QWidget* m_widget;
    QStandardItemModel* m_model;
    QTableView* m_view;
    static Property* s_property;
    int m_index;
};

//////////////////////////////////////////////////////
class GUIPair : public QWidget {
    Q_OBJECT
public:
    GUIPair(QString varibels, QWidget* parent = nullptr);

public:
    QString getVaribels() const;
    BufForIntegral* getbuf();

public slots:
    void onTextEdit(QString textName);

private:
    QLabel* m_label;
    QLineEdit* m_lineEdit;
    QHBoxLayout* m_hBoxLayout;
};
////////////////////////////////////////////////////////
//
//class CorePair {
//private:
//    CorePair() = default;
//    ~CorePair() = default;
//public:
//    static CorePair* getCorePair();
//
//private:
//    std::list<BufForIntegral*> m_pairs;
//    static CorePair* s_corePair;
//}
//
/**************************************************************/

class WindowForVaribels : public QDockWidget
{
private:
    WindowForVaribels(const QString& title, QWidget* parent = nullptr);

public:
    static void creatWindowForVaribels(const QString& title, QWidget* parent = nullptr);
    static WindowForVaribels* getWindowForVaribels();

    void updateCore(QString func);
    void updateGui(std::list<QString>& variables);
    void clearLayout();
    void creatCorectPair();

private:

    QVBoxLayout* m_layout;
    std::list<GUIPair*> m_pairs;
    static WindowForVaribels* s_windowForVaribels;
};
