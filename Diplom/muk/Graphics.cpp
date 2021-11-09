#include "Graphics.h"
#include <QGridLayout>
#include <QGraphicsScene>
#include <QPushButton>
#include <QFrame>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QList>
#include <QPointF>
#include <iostream>
#include <cmath>
#include <QFormLayout>
#include <QTextEdit>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* widget, Graphics* parent) :
    QGraphicsView(scene, widget), m_parent(parent)
{}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
  if (event->delta() > 0) {
      m_parent->update(1.1);
  } else {
      m_parent->update(0.95);
  }
}


LineEdit::LineEdit(QString txt, QWidget* widget, Graphics* parent) :
    QLineEdit(txt, widget), m_parent(parent)
{}

void LineEdit::onTextEdit(QString textName)
{
    m_parent->changeValue(this, textName);
}


Graphics::Graphics(Integral* integral, std::string variable, double begin, double end) : QMainWindow(),
    m_integral(integral)
{
    setWindowTitle("ՆԵՐՄՈՒԾՎԱԾ ՖՈՒՆԿՑԻԱՅԻ ԳՐԱՖԻԿ");
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    setGeometry(QRect(0, 0, 1300, 1000));
    setCentralWidget(centralWidget);
    m_size = 11;
    m_segment = 80;
    m_height = 20;
    m_width = 40;
    m_lengthGraphics = (m_size - 1) * m_segment + m_width;
    m_frame = new QFrame(centralWidget);
    m_frame1 = new QFrame(centralWidget);
    m_scene = new QGraphicsScene(this);
    m_graphicsView = new GraphicsView(m_scene, m_frame, this);
    m_graphicsView->setObjectName(QStringLiteral("graphicsView"));
    m_graphicsView->setGeometry(QRect(m_width, m_height, m_lengthGraphics, m_lengthGraphics));
    m_graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	m_graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    m_frame->setObjectName(QStringLiteral("m_frame"));
    m_frame->setGeometry(QRect(0, 0, m_lengthGraphics + 2 * m_width, m_lengthGraphics + 2 * m_height));
    m_frame->setFrameShape(QFrame::StyledPanel);
    m_frame->setFrameShadow(QFrame::Raised);

    m_frame1->setObjectName(QStringLiteral("m_frame1"));
    m_frame1->setGeometry(QRect(m_lengthGraphics + 2 * m_width + m_width, 0, m_lengthGraphics + m_width, m_lengthGraphics + 2 * m_height));
    m_frame1->setFrameShape(QFrame::StyledPanel);
    m_frame1->setFrameShadow(QFrame::Raised);


    QFont font;
    font.setPointSize(6);
    setFont(font);

    m_w_lineEdit = new QLineEdit*[2 * m_size];
    m_h_lineEdit = new QLineEdit*[2 * m_size];
    for (int i = 0; i < 2 * m_size; ++i) {
        m_w_lineEdit[i] = new QLineEdit(m_frame);
        m_w_lineEdit[i]->setFont(font);
        m_w_lineEdit[i]->setEnabled(false);
        m_h_lineEdit[i] = new QLineEdit(m_frame);
        m_h_lineEdit[i]->setFont(font);
        m_h_lineEdit[i]->setEnabled(false);
    }
    for (int i = 0; i < m_size; ++i) {
        m_w_lineEdit[i]->setGeometry(QRect(m_width + (i * m_segment) , 0, m_width, m_height));
        m_w_lineEdit[m_size + i]->setGeometry(QRect(m_width + (i * m_segment) , m_frame->height() - m_height , m_width, m_height));
    }
    for (int i = 0; i < m_size; ++i) {
        m_h_lineEdit[i]->setGeometry(QRect(0, m_height + (i * m_segment), m_width, m_height));
        m_h_lineEdit[m_size + i]->setGeometry(QRect(m_frame->width() - m_width, m_height + (i * m_segment), m_width, m_height));
    }

    m_w = new double[m_size];
    m_h = new double[m_size];
    m_count = 1000;
    m_variable = variable;
    start(begin, end);
}

Graphics::~Graphics()
{
    delete[] m_w;
    delete[] m_h;
}

void Graphics::setvalueLineEdit()
{
    for (int i = 0; i < m_size; ++i) {
        m_w_lineEdit[i]->setText(QString::number(m_w[i]));
        m_w_lineEdit[m_size + i]->setText(QString::number(m_w[i]));
    }
    for (int i = 0; i < m_size; ++i) {
        m_h_lineEdit[i]->setText(QString::number(m_h[i]));
        m_h_lineEdit[m_size + i]->setText(QString::number(m_h[i]));
    }
}

void Graphics::setAxisDefaultValues(double begin, double end)
{
  //  for (int i = 0; i < m_size; ++i) {
  //      m_w[i] = -50 + (i*10);
  //      m_h[i] = 50 - (i*10);
  //  }
    double rangeCount = m_size - 1;
    double rangeW = end - begin;
    const double h_w = abs(rangeW) / rangeCount;
    m_w[0] = begin;
    for (int i = 1; i < m_size - 1; ++i) {
         m_w[i] = m_w[i - 1] + h_w;
    }
    m_w[m_size - 1] = end;
    uptadeYCoordinate();
}

void Graphics::uptadeYCoordinate()
{
    double rangeCount = m_size - 1;
    double beginH = m_integral->Function(m_pairs, m_variable, m_w[0]);
    double endH = m_integral->Function(m_pairs, m_variable, m_w[m_size - 1]);
    if (endH < beginH) {
        std::swap(endH, beginH);
    }
    int count = m_count;
    double h = (m_w[1] - m_w[0]) / count;
    double val;
    double value;
    for (int i = 0; i < m_size - 1; i++) {
        val = m_w[i];
        for (int j = 0; j < count; ++j) {
            value = m_integral->Function(m_pairs, m_variable, val);
            if (value > endH) {
                endH = value;
            } else if (value < beginH) {
                beginH = value;
            }
            val += h;
        }
    }
    double rangeH = endH - beginH;
    const double h_h = abs(rangeH) / rangeCount;
    m_h[0] = endH;
    for (int i = 1; i < m_size - 1; ++i) {
         m_h[i] = m_h[i - 1] - h_h;
    }
    m_h[m_size - 1] = beginH;
}

void Graphics::update(double value)
{
    start(m_w[0] * value, m_w[m_size - 1] * value);
}

void Graphics::coreUpdate()
{
    m_scene->clear();
    setvalueLineEdit();
    drawNet();
    drawGraf();
}

void Graphics::drawNet()
{
    QPen pen(Qt::gray);
    for (int i = 0; i < m_size; ++i) {
        if (m_w[i] == 0) {
            pen.setColor(Qt::black);
        } else {
            pen.setColor(Qt::gray);
        }
        m_scene->addLine(m_width / 2 + (i * m_segment), 0, m_width / 2 + (i * m_segment), m_lengthGraphics, pen);
    }
    for (int i = 0; i < m_size; ++i) {
        if (m_h[i] == 0) {
            pen.setColor(Qt::black);
        } else {
            pen.setColor(Qt::gray);
        }
        m_scene->addLine(0, m_height / 2 + (i * m_segment), m_lengthGraphics, m_height / 2 + (i * m_segment), pen);
    }
}

void Graphics::drawGraf()
{
    QList<QPointF> points;
    QPointF p;
    double value;
    double val;
    double min = 0;
    double max = m_lengthGraphics;
    double h = (m_w[1] - m_w[0]) / m_count;
    for (int i = 0; i < m_size - 1; i++) {
        val = m_w[i];
        for (int j = 0; j < m_count; ++j) {
            value = m_integral->Function(m_pairs, m_variable, val);
            double y = getvalueH(value);
            double x = getvalueW(val);
            if (x >= min && max >= x && y >= min && max >= y) {
                p = QPointF(QPoint(x, y));
                points.append(p);
            }
            val += h;
        }
    }
    if (points.size() == 0) {
        return;
    }
    QPainterPath* path = new QPainterPath();
    path->moveTo(points[0]);
    for (int i = 1; i < points.count(); i++) {
        path->lineTo(points[i]);
    }
    QPen pen(Qt::darkGreen);
    m_scene->addPath(*path, pen);
    delete path;
}

double Graphics::getvalueW(double value)
{
    double delta = (m_w[1] - m_w[0]) / double(m_count);
    double count = (value - m_w[0]) / delta;
    double h = m_segment / double(m_count);
    return (m_width / 2) + count * h;
}

double Graphics::getvalueH(double value)
{
    double delta = (m_h[0] - m_h[1]) / double(m_count);
    double count = (m_h[0] - value ) / delta;
    double h = m_segment / double(m_count);
    return (m_height / 2) + count * h;
}

void Graphics::setIntegral(Integral* integral)
{
    delete m_integral;
    m_integral = integral;
}

void Graphics::start(double begin, double end)
{
    init();
    setAxisDefaultValues(begin, end);
    coreUpdate();
}

void Graphics::init()
{
    std::list<std::string> variables;
    m_integral->getVariables(variables);
    m_countVaribales = variables.size() - 1;
    m_label = new QLabel*[m_countVaribales];
    m_result = new LineEdit*[m_countVaribales];
    QFormLayout *layout = new QFormLayout();
    BufForIntegral buf;
    QFont font;
    font.setPointSize(11);
    QWidget *window = new QWidget(m_frame1);
    auto it = variables.begin();
    for (int i = 0; i < m_countVaribales + 1, it != variables.end(); ++i, ++it) {
        if (*it != m_variable) {
            m_label[i] = new QLabel(QString((*it).c_str()), window);
            m_label[i]->setFont(font);
            m_result[i] = new LineEdit( "1", window, this);
            m_result[i]->setFont(font);
            connect(m_result[i], SIGNAL(textEdited(QString)), m_result[i], SLOT(onTextEdit(QString)));
            layout->addRow(m_label[i], m_result[i]);
            buf.setDoubleValue("1");
            buf.setVariableName((*it));
            m_pairs.push_back(buf);
        }
    }
    window->setLayout(layout);
}

void Graphics::getbufs(std::list<BufForIntegral>& pairs)
{
    pairs.clear();
    pairs.insert(pairs.end(), m_pairs.begin(), m_pairs.end());
}

void Graphics::changeValue(LineEdit* lEdit, QString textName)
{
    if (textName.isEmpty()) {
        return;
    }
    if (!Helper::isNumberZ(textName.toStdString())) {
        return;
    }
    int i = 0;
    for (; i < m_countVaribales; i++) {
        if (m_result[i] == lEdit) {
            break;
        }
        std::list<BufForIntegral>::iterator it = m_pairs.begin();
        std::advance(it, i);
        it->setDoubleValue(textName.toStdString());
    }
    std::cout << textName.toStdString() << std::endl;
    m_integral->updateFunction();
    start(m_w[0], m_w[m_size - 1]);
}
