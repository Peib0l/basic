#include "paintwidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
//    m_nInitialX = 0;
//    m_nInitialY = 0;
//    m_nFinalX = 0;
//    m_nFinalY = 0;
//    m_nPTargetPixmap = 0;
//    m_nPTargetPixmap = new QPixmap(400,400);
    m_nPTargetPixmap = QPixmap(400,400);
    m_nPTargetPixmap.fill();
    m_nbMousePressed = false;
}

PaintWidget::~PaintWidget()
{
//    delete ui;
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    m_nbMousePressed = true;
//    m_nInitialX = event->pos().x();
//    m_nInitialY = event->pos().y();

    //LINE
//    m_line.setP1(event->pos());
//    m_line.setP2(event->pos());

    //ARC
    rect.setBottomLeft(event->pos());
    rect.setTopRight(event->pos());
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
//        QPainter PixmapPainter(m_nPTargetPixmap);
//        QPen pen(Qt::black);
//        PixmapPainter.setPen(pen);
//        PixmapPainter.drawLine(m_nInitialX, m_nInitialY, m_nFinalX, m_nFinalY);
//        m_nFinalX = event->pos().x();
//        m_nFinalY = event->pos().y();

        //LINE
//       m_line.setP2(event->pos());
//        update(); // update your view

        //ARC
        rect.setTopRight(event->pos());
    }
    update(); // update your view
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_nbMousePressed = false;
    update();
}

void PaintWidget::paintEvent(QPaintEvent *e)
{
    static bool wasPressed = false;
    int startAngle = 20*16;
    int arcLength = 120*16;

    QLinearGradient linearGrad(QPointF(100, 100), QPointF(200, 200));
        linearGrad.setColorAt(0, Qt::black);
        linearGrad.setColorAt(1, Qt::green);


    QPainter painter(this);

    if(m_nbMousePressed)
    {
        painter.drawPixmap(0, 0, m_nPTargetPixmap);

        //LINE
//        painter.drawLine(m_line);
//        wasPressed = true;

        //ARC
        painter.drawArc(rect,startAngle,arcLength);
        wasPressed = true;
    }
    else if(wasPressed)
    {
        QPainter PixmapPainter(&m_nPTargetPixmap);
        QPen pen(linearGrad, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        PixmapPainter.setPen(pen);

        //LINE
//        PixmapPainter.drawLine(m_line);

        //ARC
        PixmapPainter.drawArc(rect,startAngle,arcLength);

        painter.drawPixmap(0, 0, m_nPTargetPixmap);
        wasPressed = false;
    }
}


