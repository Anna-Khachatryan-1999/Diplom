#pragma once
#include <QMainWindow>
#include <QObject>

class QWidget;
class QLabel;
class QTextEdit;
class QPushButton;
class QTextEdit;
class QMenuBar;
class QToolBar;
class QStatusBar;
class QComboBox;
class Graphics;
class QLineEdit;
class Help;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

public:
     void retranslateUi(QMainWindow *MainWindow);

private slots:
     void on_pushButton_clicked();
     void on_deleteFunction_clicked();
     void on_addition_clicked();
     void on_removes_clicked();
     void on_multiplication_clicked();
     void on_root_clicked();
     void on_bracket1_clicked();
     void on_division_clicked();
     void on_degree_clicked();
     void on_bracket2_clicked();
     void on_pi_clicked();
     void on_infinite1_clicked();
     void on_infinite2_clicked();
     void on_grafik_clicked();
     void on_help_clicked();
     void on_combo_Box_Items(const QString& text);
     void onTextEdit(QString textName);

private:
    QWidget *centralWidget;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QTextEdit *textEdit_3;
    QLabel *label_3;
    QLabel *Label_pic;
    QLabel *Label_pic1;
    QComboBox *dVariable;
    QTextEdit *result;
    QComboBox *algoritms;
    QLabel *algorimtms;
    QTextEdit *Splits;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    Graphics *m_graphics;
    QLineEdit *function;
    QLabel *label_12;
    QPushButton *deleteFunction;
    QPushButton *addition;
    QPushButton *removes;
    QPushButton *multiplication;
    QPushButton *root;
    QPushButton *bracket_1;
    QPushButton *division;
    QPushButton *degree;
    QPushButton *bracket_2;
    QPushButton *pi;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *limit1;
    QLineEdit *limit2;
    QPushButton *infinite_1;
    QPushButton *infinite_2;
    QLineEdit *variable;
    QLineEdit *equal;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_24;
    QPushButton *grafik;
    QPushButton *help;
    Help *m_help;
    QComboBox *comboBoxFunc;
};
