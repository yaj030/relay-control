#ifndef QCIRINDICATOR_H
#define QCIRINDICATOR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class QCirIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit QCirIndicator(QWidget *parent);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void turnGreen();
    void turnRed();
private:
    bool status;
};

#endif // QCIRINDICATOR_H
