#include "window.h"
#include "Graphics.h"
#include "Property.h"
#include "Help.h"
#include "Property.h"
#include "Integral.h"

#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>
#include <QComboBox>
#include <QMessageBox>
#include <limits>
#include <QMdiArea>
#include <QVBoxLayout>
#include <iostream>
#include <cmath>

namespace {
    void test() {
        std::string func = "e^x";
        int b = 1;
        int e = 2;
        double corectCount = exp(2) - exp(1);
        double count;
        Integral inter(func);
        std::list<BufForIntegral> pairs;
        std::cout << "size\t\t\t\terrors";
        for (int i = 0; i <= 1000000;  i+= 10000) {
            count = inter.integralMetodLeftRectangles(pairs, "x", b, e, i);
            std::cout << i << "\t\t\t\t" << ((count > corectCount) ? (count - corectCount) : (corectCount - count)) << std::endl;
        }
    }
}

Window::Window() : QMainWindow()
{
    test();
    setObjectName(QStringLiteral("MainWindow"));
    this->setFixedSize(1393, 848);
    m_graphics = nullptr;
    QFont font;
    font.setPointSize(9);
    font.setBold(true);
    font.setItalic(true);
    font.setWeight(75);
    setFont(font);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    label = new QLabel(centralWidget);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(430, 0, 501, 81));
    QFont fontk;
    fontk.setPointSize(20);
    label->setFont(fontk);
    textEdit = new QTextEdit(centralWidget);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setGeometry(QRect(100, 480, 231, 61));
    QFont font1;
    font1.setPointSize(13);
    font1.setBold(true);
    font1.setWeight(75);
    textEdit->setFont(font1);
    textEdit->setEnabled(false);
    pushButton = new QPushButton(centralWidget);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    pushButton->setGeometry(QRect(1060, 170, 101, 31));
    QFont font2;
    font2.setPointSize(9);
    font2.setBold(true);
    font2.setWeight(75);
    pushButton->setFont(font2);
    pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    textEdit_2 = new QTextEdit(centralWidget);
    textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
    textEdit_2->setGeometry(QRect(20, 580, 61, 31));
    QFont fontx;
    fontx.setPointSize(10);
    fontx.setBold(true);
    fontx.setWeight(75);
    textEdit_2->setFont(fontx);
    textEdit_2->setEnabled(false);
    label_2 = new QLabel(centralWidget);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(370, 210, 111, 31));
    textEdit_3 = new QTextEdit(centralWidget);
    textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
    textEdit_3->setGeometry(QRect(20, 410, 61, 31));
    QFont font3;
    font3.setPointSize(10);
    font3.setBold(true);
    font3.setItalic(false);
    font3.setWeight(75);
    textEdit_3->setFont(font3);
    textEdit_3->setEnabled(false);
    label_3 = new QLabel(centralWidget);
    label_3->setObjectName(QStringLiteral("label_3"));
    label_3->setGeometry(QRect(370, 240, 121, 41));
    Label_pic = new QLabel(centralWidget);
    Label_pic->setObjectName(QStringLiteral("Label_pic"));
    Label_pic->setGeometry(QRect(20, 450, 71, 121));
    Label_pic1 = new QLabel(centralWidget);
    Label_pic1->setObjectName(QStringLiteral("Label_pic1"));
    Label_pic1->setGeometry(QRect(300, 10, 111, 71));
    result = new QTextEdit(centralWidget);
    result->setObjectName(QStringLiteral("result"));
    result->setGeometry(QRect(450, 490, 191, 51));
    algoritms = new QComboBox(centralWidget);
    algoritms->setObjectName(QStringLiteral("algoritms"));
    algoritms->setGeometry(QRect(720, 170, 271, 31));
    algoritms->setCursor(QCursor(Qt::PointingHandCursor));
    algorimtms = new QLabel(centralWidget);
    algorimtms->setObjectName(QStringLiteral("algorimtms"));
    algorimtms->setGeometry(QRect(40, 400, 81, 21));
    QFont font4;
    font4.setPointSize(11);
    font4.setItalic(true);
    algorimtms->setFont(font4);
    Splits = new QTextEdit(centralWidget);
    Splits->setObjectName(QStringLiteral("Splits"));
    Splits->setGeometry(QRect(580, 290, 91, 31));
    Splits->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
    label_5 = new QLabel(centralWidget);
    label_5->setObjectName(QStringLiteral("label_5"));
    label_5->setGeometry(QRect(180, 630, 91, 17));
    label_6 = new QLabel(centralWidget);
    label_6->setObjectName(QStringLiteral("label_6"));
    label_6->setGeometry(QRect(360, 630, 54, 17));
    label_7 = new QLabel(centralWidget);
    label_7->setObjectName(QStringLiteral("label_7"));
    label_7->setGeometry(QRect(510, 630, 54, 17));
    label_8 = new QLabel(centralWidget);
    label_8->setObjectName(QStringLiteral("label_8"));
    label_8->setGeometry(QRect(40, 570, 54, 17));
    QFont font6;
    font6.setPointSize(11);
    label_8->setFont(font6);
    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1232, 23));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    setStatusBar(statusBar);
    label_9 = new QLabel(centralWidget);
    label_9->setObjectName(QStringLiteral("label_9"));
    label_9->setGeometry(QRect(340, 500, 20, 31));
    QFont font8;
    font8.setPointSize(17);
    label_9->setFont(font8);
    dVariable = new QComboBox(centralWidget);
    dVariable->setObjectName(QStringLiteral("dVariable"));
    dVariable->setGeometry(QRect(610, 170, 61, 31));
    QFont fontv;
    fontv.setPointSize(12);
    dVariable->setFont(fontv);
    dVariable->setCursor(QCursor(Qt::PointingHandCursor));
    QFont fonty;
    fonty.setPointSize(11);
    function = new QLineEdit(centralWidget);
    function->setObjectName(QStringLiteral("function"));
    function->setGeometry(QRect(10, 170, 321, 29));
    function->setCursor(QCursor(Qt::PointingHandCursor));
    label_12 = new QLabel(centralWidget);
    label_12->setObjectName(QStringLiteral("label_12"));
    label_12->setGeometry(QRect(10, 130, 171, 31));
    deleteFunction = new QPushButton(centralWidget);
    deleteFunction->setObjectName(QStringLiteral("deleteFunction"));
    deleteFunction->setGeometry(QRect(10, 200, 51, 29));
    QFont font9;
    font9.setBold(false);
    font9.setWeight(50);
    deleteFunction->setFont(font9);
    deleteFunction->setCursor(QCursor(Qt::PointingHandCursor));
    deleteFunction->setStyleSheet(QStringLiteral("background-color:rgb(255, 170, 127)"));
    addition = new QPushButton(centralWidget);
    addition->setObjectName(QStringLiteral("addition"));
    addition->setGeometry(QRect(60, 200, 31, 29));
    QFont font10;
    font10.setFamily(QStringLiteral("Noto Sans"));
    font10.setPointSize(10);
    addition->setFont(font10);
    addition->setCursor(QCursor(Qt::PointingHandCursor));
    removes = new QPushButton(centralWidget);
    removes->setObjectName(QStringLiteral("removes"));
    removes->setGeometry(QRect(90, 200, 31, 29));
    removes->setCursor(QCursor(Qt::PointingHandCursor));
    //removes->setStyleSheet("background-color: rgb(255,255,0);");
    //removes->setStyleSheet("color: red; background-color: red");
    multiplication = new QPushButton(centralWidget);
    multiplication->setObjectName(QStringLiteral("multiplication"));
    multiplication->setGeometry(QRect(120, 200, 31, 29));
    multiplication->setCursor(QCursor(Qt::PointingHandCursor));
    root = new QPushButton(centralWidget);
    root->setObjectName(QStringLiteral("root"));
    root->setGeometry(QRect(210, 200, 31, 29));
    root->setCursor(QCursor(Qt::PointingHandCursor));
    bracket_1 = new QPushButton(centralWidget);
    bracket_1->setObjectName(QStringLiteral("bracket_1"));
    bracket_1->setGeometry(QRect(240, 200, 31, 29));
    bracket_1->setCursor(QCursor(Qt::PointingHandCursor));
    division = new QPushButton(centralWidget);
    division->setObjectName(QStringLiteral("division"));
    division->setGeometry(QRect(150, 200, 31, 29));
    division->setCursor(QCursor(Qt::PointingHandCursor));
    degree = new QPushButton(centralWidget);
    degree->setObjectName(QStringLiteral("degree"));
    degree->setGeometry(QRect(180, 200, 31, 29));
    degree->setCursor(QCursor(Qt::PointingHandCursor));
    bracket_2 = new QPushButton(centralWidget);
    bracket_2->setObjectName(QStringLiteral("bracket_2"));
    bracket_2->setGeometry(QRect(270, 200, 31, 29));
    bracket_2->setCursor(QCursor(Qt::PointingHandCursor));
    pi = new QPushButton(centralWidget);
    pi->setObjectName(QStringLiteral("pi"));
    pi->setGeometry(QRect(300, 200, 31, 29));
    pi->setCursor(QCursor(Qt::PointingHandCursor));
    label_13 = new QLabel(centralWidget);
    label_13->setObjectName(QStringLiteral("label_13"));
    label_13->setGeometry(QRect(20, 370, 191, 21));
    label_13->setFont(fonty);
    label_14 = new QLabel(centralWidget);
    label_14->setObjectName(QStringLiteral("label_14"));
    label_14->setGeometry(QRect(370, 130, 91, 31));
    label_15 = new QLabel(centralWidget);
    label_15->setObjectName(QStringLiteral("label_15"));
    label_15->setGeometry(QRect(370, 170, 191, 31));
    limit1 = new QLineEdit(centralWidget);
    limit1->setObjectName(QStringLiteral("limit1"));
    limit1->setGeometry(QRect(600, 210, 31, 29));
    limit1->setCursor(QCursor(Qt::PointingHandCursor));
    limit1->setCursorMoveStyle(Qt::LogicalMoveStyle);
    limit2 = new QLineEdit(centralWidget);
    limit2->setObjectName(QStringLiteral("limit2"));
    limit2->setGeometry(QRect(600, 240, 31, 29));
    limit2->setCursor(QCursor(Qt::PointingHandCursor));
    infinite_1 = new QPushButton(centralWidget);
    infinite_1->setObjectName(QStringLiteral("infinite_1"));
    infinite_1->setGeometry(QRect(630, 210, 41, 29));
    QFont font11;
    font11.setPointSize(10);
    infinite_1->setFont(font11);
    infinite_1->setCursor(QCursor(Qt::PointingHandCursor));
    infinite_2 = new QPushButton(centralWidget);
    infinite_2->setObjectName(QStringLiteral("infinite_2"));
    infinite_2->setGeometry(QRect(630, 240, 41, 29));
    infinite_2->setFont(font11);
    infinite_2->setCursor(QCursor(Qt::PointingHandCursor));
    label_16 = new QLabel(centralWidget);
    label_16->setObjectName(QStringLiteral("label_16"));
    label_16->setGeometry(QRect(720, 130, 161, 31));
    label_17 = new QLabel(centralWidget);
    label_17->setObjectName(QStringLiteral("label_17"));
    label_17->setGeometry(QRect(1060, 130, 141, 31));
    variable = new QLineEdit(centralWidget);
    variable->setObjectName(QStringLiteral("variable"));
    variable->setGeometry(QRect(360, 500, 51, 29));
    QFont font12;
    font12.setPointSize(14);
    variable->setFont(font12);
    variable->setEnabled(false);
    equal = new QLineEdit(centralWidget);
    equal->setObjectName(QStringLiteral("equal"));
    equal->setGeometry(QRect(420, 500, 21, 29));
    equal->setFont(font12);
    equal->setCursor(QCursor(Qt::ArrowCursor));
    label_18 = new QLabel(centralWidget);
    label_18->setObjectName(QStringLiteral("label_18"));
    label_18->setGeometry(QRect(370, 290, 191, 17));
    label_19 = new QLabel(centralWidget);
    label_19->setObjectName(QStringLiteral("label_19"));
    label_19->setGeometry(QRect(370, 310, 81, 17));
    label_24 = new QLabel(centralWidget);
    label_24->setObjectName(QStringLiteral("label_24"));
    label_24->setGeometry(QRect(30, 670, 371, 21));
    label_24->setFont(font11);
    grafik = new QPushButton(centralWidget);
    grafik->setObjectName(QStringLiteral("grafik"));
    grafik->setGeometry(QRect(120, 710, 161, 51));
    comboBoxFunc = new QComboBox(centralWidget);
    comboBoxFunc->setObjectName(QStringLiteral("comboBoxFunc"));
    comboBoxFunc->setGeometry(QRect(260, 240, 69, 25));
    help = new QPushButton(centralWidget);
    help->setObjectName(QStringLiteral("help"));
    help->setGeometry(QRect(1280, 0, 121, 31));



    retranslateUi(this);

    QPixmap pix("/home/anna/Desktop/Untitled Folder/images.jpg");
    QPixmap pix1("/home/anna/Desktop/Untitled Folder/images.png");

    Label_pic->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    Label_pic1->setPixmap(pix1.scaled(110,110,Qt::KeepAspectRatio));
    result->setEnabled(false);
    limit1->setText(QString::number(1));
    limit2->setText(QString::number(0));
    Splits->setText(QString::number(100000));

    QObject::connect(pushButton, SIGNAL(clicked()), this , SLOT(on_pushButton_clicked()));
    QObject::connect(deleteFunction, SIGNAL(clicked()), this , SLOT(on_deleteFunction_clicked()));
    QObject::connect(addition, SIGNAL(clicked()), this , SLOT(on_addition_clicked()));
    QObject::connect(removes, SIGNAL(clicked()), this , SLOT(on_removes_clicked()));
    QObject::connect(multiplication, SIGNAL(clicked()), this , SLOT(on_multiplication_clicked()));
    QObject::connect(root, SIGNAL(clicked()), this , SLOT(on_root_clicked()));
    QObject::connect(bracket_1, SIGNAL(clicked()), this , SLOT(on_bracket1_clicked()));
    QObject::connect(division, SIGNAL(clicked()), this , SLOT(on_division_clicked()));
    QObject::connect(degree, SIGNAL(clicked()), this , SLOT(on_degree_clicked()));
    QObject::connect(bracket_2, SIGNAL(clicked()), this , SLOT(on_bracket2_clicked()));
    QObject::connect(pi, SIGNAL(clicked()), this , SLOT(on_pi_clicked()));
    QObject::connect(infinite_1, SIGNAL(clicked()), this , SLOT(on_infinite1_clicked()));
    QObject::connect(infinite_2, SIGNAL(clicked()), this , SLOT(on_infinite2_clicked()));
    QObject::connect(grafik, SIGNAL(clicked()), this , SLOT(on_grafik_clicked()));
    QObject::connect(help, SIGNAL(clicked()), this , SLOT(on_help_clicked()));
    QObject::connect(comboBoxFunc, SIGNAL(currentTextChanged(const QString&)), this , SLOT(on_combo_Box_Items(const QString&)));
    connect(function, SIGNAL(textEdited(QString)), this, SLOT(onTextEdit(QString)));

    Property::creatProperty(tr("                                                   Տարբեր ինտեգրալների արդյունքները"), centralWidget);
    Property* prop = Property::getProperty();

    WindowForVaribels::creatWindowForVaribels("hgfdgjfghfsdjkfhdf", centralWidget);
}

void Window::retranslateUi(QMainWindow *mainWindow)
{
        setWindowTitle(QApplication::translate("MainWindow", "Integrals", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\325\210\326\200\325\270\325\267\325\265\325\241\325\254 \325\253\325\266\325\277\325\245\325\243\326\200\325\241\325\254\325\241\325\265\325\253\325\266 \325\260\325\241\325\267\325\276\325\253\325\271</p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\324\261\326\200\325\244\325\265\325\270\326\202\325\266\326\204\325\250", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\325\276\325\245\326\200\325\253\325\266 \325\275\325\241\325\260\325\264\325\241\325\266</p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\325\275\325\277\325\270\326\200\325\253\325\266 \325\275\325\241\325\260\325\264\325\241\325\266</p></body></html>", Q_NULLPTR));
        Label_pic->setText(QString());
        Label_pic1->setText(QString());
        algoritms->clear();
        algoritms->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\325\201\325\241\325\255 \325\270\326\202\325\262\325\262\325\241\325\266\325\257\325\265\325\270\326\202\325\266\325\266\325\245\326\200\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\324\261\325\273 \325\270\326\202\325\262\325\262\325\241\325\266\325\257\325\265\325\270\326\202\325\266\325\266\325\245\326\200\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\325\204\325\253\325\273\325\253\325\266 \325\270\326\202\325\262\325\262\325\241\325\266\325\257\325\265\325\270\326\202\325\266\325\266\325\245\326\200\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264 ", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\325\215\325\245\325\262\325\241\325\266\325\266\325\245\326\200\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\325\215\325\253\325\264\325\272\325\275\325\270\325\266\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\325\215\325\253\325\264\325\272\325\275\325\270\325\266\325\253 3/8 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\324\262\325\270\325\270\326\202\325\254\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\325\216\325\245\325\244\325\254\325\253 \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264", Q_NULLPTR)
        );       label_9->setText(QApplication::translate("MainWindow", "d", Q_NULLPTR));
        dVariable->clear();
        dVariable->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "x", Q_NULLPTR)
         << QApplication::translate("MainWindow", "a", Q_NULLPTR)
         << QApplication::translate("MainWindow", "b", Q_NULLPTR)
         << QApplication::translate("MainWindow", "c", Q_NULLPTR)
         << QApplication::translate("MainWindow", "d", Q_NULLPTR)
         << QApplication::translate("MainWindow", "f", Q_NULLPTR)
         << QApplication::translate("MainWindow", "g", Q_NULLPTR)
         << QApplication::translate("MainWindow", "h", Q_NULLPTR)
         << QApplication::translate("MainWindow", "j", Q_NULLPTR)
         << QApplication::translate("MainWindow", "k", Q_NULLPTR)
         << QApplication::translate("MainWindow", "l", Q_NULLPTR)
         << QApplication::translate("MainWindow", "m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "n", Q_NULLPTR)
         << QApplication::translate("MainWindow", "p", Q_NULLPTR)
         << QApplication::translate("MainWindow", "q", Q_NULLPTR)
         << QApplication::translate("MainWindow", "r", Q_NULLPTR)
         << QApplication::translate("MainWindow", "s", Q_NULLPTR)
         << QApplication::translate("MainWindow", "t", Q_NULLPTR)
         << QApplication::translate("MainWindow", "u", Q_NULLPTR)
         << QApplication::translate("MainWindow", "v", Q_NULLPTR)
         << QApplication::translate("MainWindow", "w", Q_NULLPTR)
         << QApplication::translate("MainWindow", "y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "z", Q_NULLPTR)
        );
        function->setText(QApplication::translate("MainWindow", "x+cos(x)+x+l+y", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\325\266\325\245\326\200\325\264\325\270\326\202\325\256\325\245\326\204    \326\206\325\270\326\202\325\266\325\257\326\201\325\253\325\241\325\266", Q_NULLPTR));
        deleteFunction->setText(QApplication::translate("MainWindow", "\325\273\325\266\325\273\325\245\325\254", Q_NULLPTR));
        addition->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        removes->setText(QApplication::translate("MainWindow", "\326\212", Q_NULLPTR));
        multiplication->setText(QApplication::translate("MainWindow", "*", Q_NULLPTR));
        root->setText(QApplication::translate("MainWindow", "\342\210\232", Q_NULLPTR));
        bracket_1->setText(QApplication::translate("MainWindow", "(", Q_NULLPTR));
        division->setText(QApplication::translate("MainWindow", "/", Q_NULLPTR));
        degree->setText(QApplication::translate("MainWindow", "^", Q_NULLPTR));
        bracket_2->setText(QApplication::translate("MainWindow", ")", Q_NULLPTR));
        pi->setText(QApplication::translate("MainWindow", "π", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\324\277\325\275\325\277\325\241\326\201\325\276\325\253 \325\260\325\245\325\277\326\207\325\265\325\241\325\254\325\250\325\235", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "\324\270\325\266\325\277\326\200\325\245\326\204 \325\235", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "\325\253\325\266\325\277\325\245\325\243\326\200\325\264\325\241\325\266 \326\203\325\270\326\203\325\270\325\255\325\241\325\257\325\241\325\266", Q_NULLPTR));
        infinite_1->setText(QApplication::translate("MainWindow", "+\342\210\236", Q_NULLPTR));
        infinite_2->setText(QApplication::translate("MainWindow", "-\342\210\236", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "\325\210\326\200\325\270\325\267\325\245\326\204  \325\241\325\254\325\243\325\270\326\200\325\253\325\251\325\264\325\250 \325\235", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "\325\215\325\245\325\262\325\264\325\245\326\204 \325\260\325\245\325\277\326\207\325\265\325\241\325\254 \325\235", Q_NULLPTR));
        variable->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        equal->setText(QApplication::translate("MainWindow", "=", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "\325\260\325\241\325\277\325\276\325\241\325\256\325\266\325\245\326\200\325\253 \325\242\325\241\325\252\325\241\325\266\325\264\325\241\325\266 ", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "\326\204\325\241\325\266\325\241\325\257\325\250(n)", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", " \325\226\325\270\326\202\325\266\325\257\326\201\325\253\325\241\325\265\325\253  \325\243\326\200\325\241\326\206\325\253\325\257\325\250 \325\277\325\245\325\275\325\266\325\245\325\254\325\270\326\202 \325\260\325\241\325\264\325\241\326\200 \325\275\325\245\325\262\325\264\325\245\326\204 \325\235", Q_NULLPTR));
        grafik->setText(QApplication::translate("MainWindow", "\325\226\325\270\326\202\325\266\325\257\326\201\325\253\325\241\325\265\325\253 \325\243\326\200\325\241\326\206\325\253\325\257", Q_NULLPTR));
        help->setText(QApplication::translate("MainWindow", "\325\225\325\243\325\266\325\270\326\202\325\251\325\265\325\270\326\202\325\266", Q_NULLPTR));
        comboBoxFunc->clear();
        comboBoxFunc->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "cos", Q_NULLPTR)
         << QApplication::translate("MainWindow", "sin", Q_NULLPTR)
         << QApplication::translate("MainWindow", "tg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ctg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "arcsin", Q_NULLPTR)
         << QApplication::translate("MainWindow", "arccos", Q_NULLPTR)
         << QApplication::translate("MainWindow", "arctg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "arcctg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "e^", Q_NULLPTR)
         << QApplication::translate("MainWindow", "root", Q_NULLPTR)
        );
     // retranslateUi
}

void Window::on_pushButton_clicked()
{
    pushButton->setCursor(Qt::BusyCursor);
    double algoritm;
    textEdit_3->setText(limit1->text());
    textEdit_2->setText(limit2->text());
    QString sv;
    QString st;
    if (textEdit_3->toPlainText().toStdString() == "+∞") {
        sv = QString::number(std::numeric_limits<int>::max());
    } else {
        sv = textEdit_3->toPlainText();
    }
    if (textEdit_2->toPlainText().toStdString() == "-∞") {
        st = QString::number(-std::numeric_limits<int>::max());
    } else {
        st = textEdit_2->toPlainText();
    }
    QString n = Splits->toPlainText();
    QString combo = algoritms->currentText();
    std::string d = dVariable->currentText().toStdString();
    variable->clear();
    variable->insert(dVariable->currentText());
    auto start = std::chrono::high_resolution_clock::now();
    Integral* integral;
    try {
       /* std::string l = function->text().toStdString();
        int i = 0;
        while (i < l.size()){
        if (l[i] == "π"){
        std::cout << l[i] << std::endl;}
        ++i;
        }*/
    integral = new Integral(function->text().toStdString());
    } catch (Integral::InvalidParse) {
        QMessageBox msgBox;
        msgBox.setText("Կատարել եք սխալ մուտք           ");
        msgBox.exec();
        return;
    }
    if (m_graphics != nullptr) {
        delete m_graphics;
    }
    m_graphics = new Graphics(integral, d, std::stod(st.toStdString()), std::stod(sv.toStdString()));
    textEdit->setText(QString::fromStdString(integral->integralFunction()));
    std::list<BufForIntegral> pairs;
    m_graphics->getbufs(pairs);
    if (combo == "Ձախ ուղղանկյունների ալգորիթմ") {
        algoritm = integral->integralMetodLeftRectangles(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Աջ ուղղանկյունների ալգորիթմ") {
        algoritm = integral->integralMetodRightRectangles(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Միջին ուղղանկյունների ալգորիթմ ") {
        algoritm = integral->integralMetodAverageRectangles(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Սեղանների ալգորիթմ") {
        algoritm = integral->integralMetodTables(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Սիմպսոնի ալգորիթմ") {
        algoritm = integral->integralMetodSimpson(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Սիմպսոնի 3/8 ալգորիթմ") {
        algoritm = integral->integralMetodSimpsonThreeEighths(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Բոուլի ալգորիթմ") {
        algoritm = integral->integralMetodBoole(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    } else if (combo == "Վեդլի ալգորիթմ") {
        algoritm = integral->integralMetodWeddles(pairs, d,
                                       std::stod(st.toStdString()),
                                       std::stod(sv.toStdString()),
                                       std::stod(n.toStdString()));
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto time = stop - start;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    QString qtime;
    qtime += QString::number(seconds.count());
    qtime += QString(" : ");
    qtime += QString::number(milliseconds.count());


    result->setText(QString::fromStdString( (std::to_string(algoritm))));
    QString item;
    if (combo == "Ձախ ուղղանկյունների ալգորիթմ") {
        item = "Ձ․ուղղ․";
    } else if (combo == "Աջ ուղղանկյունների ալգորիթմ") {
        item = "Ա․ուղղ․";
    } else if (combo == "Միջին ուղղանկյունների ալգորիթմ ") {
        item = "Մ․ուղղ․";
    } else if (combo == "Սեղանների ալգորիթմ") {
        item = "Սեղ․";
    } else if (combo == "Սիմպսոնի ալգորիթմ") {
        item = "Սիմպ․";
    } else if (combo == "Սիմպսոնի 3/8 ալգորիթմ") {
        item = "Սիմպ․ 3/8";
    } else if (combo == "Բոուլի ալգորիթմ") {
        item = "Բոուլ․";
    } else if (combo == "Վեդլի ալգորիթմ") {
        item = "Վեդլ․";
    }


    Property::getProperty()->addItem(PropertyItem(function->text(), QString::number(algoritm), item, n, qtime));

    pushButton->setCursor(Qt::PointingHandCursor);
}

void Window::on_deleteFunction_clicked()
{
    function->clear();
}

void Window::on_addition_clicked()
{
    function->insert("+");
}

void Window::on_removes_clicked()
{
    function->insert("-");
}

void Window::on_multiplication_clicked()
{
    function->insert("*");
}

void Window::on_root_clicked()
{
    function->insert("root");
}

void Window::on_bracket1_clicked()
{
    function->insert("(");
}

void Window::on_division_clicked()
{
    function->insert("/");
}

void Window::on_degree_clicked()
{
    function->insert("^");
}

void Window::on_bracket2_clicked()
{
    function->insert(")");
}

void Window::on_pi_clicked()
{
    function->insert("π");
}

void Window::on_combo_Box_Items(const QString& text)
{
    function->insert(text);
}

void Window::on_infinite1_clicked()
{
    limit1->clear();
    limit1->setText(QString::fromStdString("+∞"));
}

void Window::on_infinite2_clicked()
{
    limit2->clear();
    limit2->setText(QString::fromStdString("-∞"));
}

void Window::on_grafik_clicked()
{
    if (m_graphics == nullptr) {
        QMessageBox msgBox;
        msgBox.setText("Նախ սեղմեք «Արդյունքը» կոճակը           ");
        msgBox.exec();
        return;
    }
    m_graphics->show();
}

void Window::on_help_clicked()
{
    m_help = new Help();
    m_help->show();
}

void Window::onTextEdit(QString textName)
{
    //std::cout<< "jhdhduheh    ------ " << textName.toStdString() << std::endl;
    //WindowForVaribels* ptr = WindowForVaribels::getWindowForVaribels();
    //ptr->updateCore(textName);
}
