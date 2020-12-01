#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
//first way: class Ui_Form; //this is forward declaration,from qt pattern book, has to include ui_form.h file in the cpp
//#include "ui_form.h" // it looks like this works too. don't need to include this in the cpp file
//the third way is like what in the main window, has namespace here, use Ui:Form *m_ui instead of Ui_Form *m_ui line 25, include ui_form.h in the cpp
#include "relay.h"
#include <QList>
#include <QMessageBox>
#include <QTimer>
#include <QListIterator>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class Form;
}

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = 0);

    void updateStatus();
    void setRelay(relay* _relay);
    void setStatus(bool _status);

signals:

public slots:

private slots:
    void turnOn();
    void turnOff();

    void startRunOsc();
    void setHalfPeriod(int valueChanged);
    void setTotalTime(int valueChanged);
    void setFirstTurnOnTime(int valueChanged);

    void startSinglePulse();
    void setPulseStartTime(int valueChanged);
    void setPulseStopTime(int valueChanged);

    void stopRun();
    void showRemaining();
    void switchStatus();
    void runTask();

    void openTimeFile();
    bool isTimePointsSorted();
    void startCustom();

private:
 //   Ui_Form *m_ui;
    Ui::Form *m_ui;
    relay *m_relay;
    bool status;

    void makeOscTimePoints();
    int halfPeriod;
    int totalTime;
    int firstTurnOnTime;

    void makeSinglePulseTimePoints();
    int pulseStartTime;
    int pulseStopTime;

    QString timeFileName;
    bool isTimeSorted;

    QTimer timer;
    QTimer queryTimer;
    QList<int> timepoints;
    QList<int> timepointsDiff;
    QListIterator<int> timeIter; //this line has to be put after the timepointsDiff line, it is in the ini list, guess the compiler has to know there is timepointsDiff

};

#endif // MYWIDGET_H
