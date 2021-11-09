#include "Property.h"
#include "Parser.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableView>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStringList>
#include <QStandardItem>
#include <QStackedLayout>
#include <QHeaderView>
#include <QFont>
#include <iostream>
#include <QLabel>
#include "Integral.h"

Property* Property::s_property = nullptr;

Property::Property(const QString& title, QWidget* parent) : QDockWidget(title, parent)
{
    setGeometry(QRect(720, 370, 671, 478));
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    font.setItalic(true);
    font.setWeight(75);
    setFont(font);
    m_widget = new QWidget(parent);
    setWidget(m_widget);
    m_layout = new QStackedLayout(m_widget);

    m_view = new QTableView();
    //m_view->verticalHeader()->hide();
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_model = new QStandardItemModel(m_view);
    QStringList horizontalHeader;
    horizontalHeader.append("ֆունկցիա");
    horizontalHeader.append("արդյունք");
    horizontalHeader.append("ալգորիթմ");
    horizontalHeader.append("քանակը(n)");
    horizontalHeader.append("ժամանակ(վ։մվ)");
    m_model->setHorizontalHeaderLabels(horizontalHeader);

    m_view->setModel(m_model);
    m_layout->addWidget(m_view);
    m_index = 0;
}

void Property::creatProperty(const QString& title, QWidget* parent)
{
    if (s_property != nullptr) {
        return;
    }
    s_property = new Property(title, parent);
}

Property* Property::getProperty()
{
    if (s_property != nullptr) {
    }
    return s_property;
}

void Property::addItem(const PropertyItem& Property_items)
{
    QStandardItem *sitem;
    sitem = new QStandardItem(Property_items.function());
    m_model->setItem(m_index, 0, sitem);
    sitem = new QStandardItem(Property_items.result());
    m_model->setItem(m_index, 1, sitem);
    sitem = new QStandardItem(Property_items.algoritm());
    m_model->setItem(m_index, 2, sitem);
    sitem = new QStandardItem(Property_items.number());
    m_model->setItem(m_index, 3, sitem);
    sitem = new QStandardItem(Property_items.time());
    m_model->setItem(m_index, 4, sitem);
    ++m_index;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


GUIPair::GUIPair(QString varibels, QWidget* parent) : QWidget(parent)
{
    m_label = new QLabel(varibels);
    m_lineEdit = new QLineEdit("1");
    m_hBoxLayout = new QHBoxLayout();
    this->setLayout(m_hBoxLayout);
    m_hBoxLayout->addWidget(m_label);
    m_hBoxLayout->addWidget(m_lineEdit);
    connect(m_lineEdit, SIGNAL(textEdited(QString)), this, SLOT(onTextEdit(QString)));
}

QString GUIPair::getVaribels() const
{
    if (m_label == nullptr) {
        return "";
    }
    m_label->text();
}

void GUIPair::onTextEdit(QString textName)
{
    if (textName.isEmpty()) {
        return;
    }
    if (!Helper::isNumberZ(textName.toStdString())) {
        m_lineEdit->clear();
        return;
    }
}

BufForIntegral* GUIPair::getbuf()
{
    BufForIntegral* buf = new BufForIntegral();
    buf->setDoubleValue(m_lineEdit->text().toStdString());
    buf->setVariableName(m_label->text().toStdString());
    return buf;
}

WindowForVaribels* WindowForVaribels::s_windowForVaribels = nullptr;

WindowForVaribels::WindowForVaribels(const QString& title, QWidget* parent)
     : QDockWidget(title, parent)
{
    setGeometry(QRect(450, 490, 330, 220));
    QWidget* widget = new QWidget(parent);
    setWidget(widget);
    m_layout = new QVBoxLayout(widget);
}

void WindowForVaribels::creatWindowForVaribels(const QString& title, QWidget* parent)
{
    if (s_windowForVaribels != nullptr) {
        return;
    }
    s_windowForVaribels = new WindowForVaribels(title, parent);
}

WindowForVaribels* WindowForVaribels::getWindowForVaribels()
{
    if (s_windowForVaribels != nullptr) {
    }
    return s_windowForVaribels;
}

void WindowForVaribels::updateCore(QString func)
{
    Parser* parser = Parser::getParser();
    std::list<std::string> words;
    if (!parser->parse(func.toStdString(), words)) {
        return;
    }
    std::list<QString> variables;
    for (const auto& litem : words) {
        if(Helper::isVariable(litem)) {
            auto find = std::find(variables.begin(), variables.end(), QString::fromStdString(litem));
            if (find != variables.end()) {
                continue;
            }
            variables.push_back(QString::fromStdString(litem));
         }
    }
    updateGui(variables);
    clearLayout();
}

void WindowForVaribels::updateGui(std::list<QString>& variables)
{
    QString qstr;
    for (auto it = m_pairs.begin(); it != m_pairs.end(); ++it) {
        qstr = (*it)->getVaribels();
        auto find = std::find(variables.begin(), variables.end(), qstr);
        if (find == variables.end()) {
            it = m_pairs.erase(it);
        } else {
            continue;
        }
    }

    for (auto item : variables) {
        bool st = false;
        for (auto litem : m_pairs) {
            if (item == litem->getVaribels()) {
                st = true;
            }
        }
        if (!st) {
            m_pairs.push_back(new GUIPair(item));
        } else {
            continue;
        }
    }

}

void WindowForVaribels::clearLayout()
{
    //while (QLayoutItem* item = m_layout->takeAt(0))
    //{
    //    if (QWidget* widget = item->widget())
    //        widget->deleteLater();
    //    delete item;
    //}
}

void WindowForVaribels::creatCorectPair()
{
    for (auto item : m_pairs) {
        m_layout->addWidget(item);
    }
}

