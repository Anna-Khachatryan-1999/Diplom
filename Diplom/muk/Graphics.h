#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <map>
#include <string>
#include "Integral.h"
#include <list>
#include <QString>
#include <QLineEdit>


class QGridLayout;
class QGraphicsScene;
class QPushButton;
class chip;
class QFrame;
class QLabel;
class Graphics;
class QTextEdit;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene* scene, QWidget* widget, Graphics* parent);
private:
    void wheelEvent(QWheelEvent *event);

private:
    Graphics* m_parent;
};

class LineEdit : public QLineEdit
{
    Q_OBJECT

public:
   LineEdit(QString txt, QWidget* widget, Graphics* parent);

public slots:
    void onTextEdit(QString textName);

private:
    Graphics* m_parent;
};


class Graphics : public QMainWindow
{
    Q_OBJECT

public:
    Graphics(Integral* integral, std::string variable, double begin, double end);
    ~Graphics();

public:
    void update(double value);
    void uptadeYCoordinate();
    void drawNet();
    void setAxisDefaultValues(double begin, double end);
    void setvalueLineEdit();
    void coreUpdate();
    void init();
    double getvalueW(double value);
    double getvalueH(double value);
    void drawGraf();
    void start(double begin, double end);
    void setIntegral(Integral* integral);
    void getbufs(std::list<BufForIntegral>& pairs);
    void changeValue(LineEdit* lEdit, QString textName);

private:
    //QGridLayout*    m_gridLayout;
    GraphicsView*  m_graphicsView;
    QGraphicsScene* m_scene;

    QWidget *centralWidget;
    QFrame *m_frame;
    QFrame *m_frame1;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    QLineEdit** m_w_lineEdit;
    QLineEdit** m_h_lineEdit;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;

    QLabel **m_label;
    LineEdit **m_result;

    double* m_w;
    double* m_h;
    int m_size;
    int m_segment;
    int m_lengthGraphics;
    int m_height;
    int m_width;
    int m_count;

    Integral* m_integral;
    std::string m_variable;
    std::list<BufForIntegral> m_pairs;
    int m_countVaribales;
};
