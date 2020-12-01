#include "qcirindicator.h"
#include <QDebug>
#include <QSize>
QCirIndicator::QCirIndicator(QWidget *parent) : QWidget(parent)
{
    status = 0;
    //setFixedSize(40,40);
    setMinimumSize(60, 60);
}
QSize QCirIndicator::sizeHint() const
{
    return QSize(80,80);
}

void QCirIndicator::paintEvent(QPaintEvent *event)
{
    // I guess need a minimal size or fixed size in the constructor, otherwise this paintEvent never got called
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    if(status)
    {
        painter.setBrush(Qt::green);
        painter.drawEllipse(this->rect());
    }
    else
    {
        painter.setBrush(Qt::red);
        painter.drawEllipse(this->rect());

    }
}

void QCirIndicator::turnGreen(){
    status = true;
    update();
}
void QCirIndicator::turnRed(){
    status = false;
    update();
}



