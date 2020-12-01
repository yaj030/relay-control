#include "mywidget.h"
//#include "ui_form.h"
#include "ui_form.h"
#include <QDebug>
#include <QThread>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Form),
    timeIter(timepointsDiff)
{
    m_ui->setupUi(this);
    isTimeSorted = false;
    halfPeriod = 1;
    totalTime = 0;
    firstTurnOnTime = 0;
    m_ui->periodInput->setValue(halfPeriod);

    connect(m_ui->turnOnButton, SIGNAL(clicked(bool)), this, SLOT(turnOn()));
    connect(m_ui->turnOffButton, SIGNAL(clicked(bool)), this, SLOT(turnOff()));

    connect(m_ui->periodInput, SIGNAL(valueChanged(int)), this, SLOT(setHalfPeriod(int)));
    connect(m_ui->totalTimeInput, SIGNAL(valueChanged(int)), this, SLOT(setTotalTime(int)));
    connect(m_ui->firstTurnOnInput, SIGNAL(valueChanged(int)), this, SLOT(setFirstTurnOnTime(int)));
    connect(m_ui->startOscButton, SIGNAL(clicked(bool)), this, SLOT(startRunOsc()));
    connect(m_ui->stopOscButton, SIGNAL(clicked(bool)), this,SLOT(stopRun()));


    connect(m_ui->pulseStartTime, SIGNAL(valueChanged(int)), this, SLOT(setPulseStartTime(int)));
    connect(m_ui->pulseStopTime, SIGNAL(valueChanged(int)), this, SLOT(setPulseStopTime(int)));
    connect(m_ui->startSingleButton, SIGNAL(clicked(bool)), this, SLOT(startSinglePulse()));
    connect(m_ui->stopSingleButton, SIGNAL(clicked(bool)), this,SLOT(stopRun()));

    connect(m_ui->startCustomButton, SIGNAL(clicked(bool)), this, SLOT(startCustom()));
    connect(m_ui->stopCustomButton, SIGNAL(clicked(bool)), this,SLOT(stopRun()));

    connect(m_ui->openFile, SIGNAL(clicked(bool)), this, SLOT(openTimeFile()));

    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(runTask()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(switchStatus()));
    connect(&queryTimer, SIGNAL(timeout()), this, SLOT(showRemaining()));
}

void myWidget::updateStatus()
{
    if(m_relay->getStatus())
    {
        setStatus(m_relay->getStatus());
        m_ui->turnOnButton->setChecked(true);
        m_ui->statusIndicator->turnGreen();
    }
    else
    {
        setStatus(m_relay->getStatus());
        m_ui->turnOffButton->setChecked(true);
        m_ui->statusIndicator->turnRed();
    }
}

void myWidget::turnOn(){
    setStatus(true);
    m_relay->turnOn();
    m_ui->statusIndicator->turnGreen();
    m_ui->turnOnButton->setChecked(true);
}

void myWidget::turnOff(){
    setStatus(false);
    m_relay->turnOff();
    m_ui->statusIndicator->turnRed();
    m_ui->turnOffButton->setChecked(true);
}

void myWidget::setRelay(relay* _relay)
{
    m_relay = _relay;
}

void myWidget::setStatus(bool _status)
{
    status = _status;
}


void myWidget::switchStatus()
{
    if(status) turnOff();
    else turnOn();
}

void myWidget::setHalfPeriod(int valueChanged)
{
    halfPeriod = valueChanged;
}
void myWidget::setTotalTime(int valueChanged)
{
    totalTime = valueChanged;
}
void myWidget::setFirstTurnOnTime(int valueChanged)
{
    firstTurnOnTime = valueChanged;
}
void myWidget::setPulseStartTime(int valueChanged)
{
    pulseStartTime = valueChanged;
}
void myWidget::setPulseStopTime(int valueChanged)
{
    pulseStopTime = valueChanged;
}

void myWidget::startRunOsc()
{
    makeOscTimePoints();
    timeIter = timepointsDiff;
    queryTimer.start(1000);
    runTask();
}
void myWidget::startSinglePulse()
{
    makeSinglePulseTimePoints();
    timeIter = timepointsDiff;
    queryTimer.start(1000);
    runTask();
}
void myWidget::startCustom()
{
    if(isTimeSorted)
    {
        timeIter = timepointsDiff;
        queryTimer.start(1000);
        runTask();
    }
    else
    {
        QMessageBox::warning(this,"Error", "time points are not sorted",
                             QMessageBox::Cancel,
                             QMessageBox::Cancel);

    }
}

void myWidget::makeOscTimePoints()
{
    timepoints.clear();
    timepointsDiff.clear();
    if(halfPeriod==0)
    {
        QMessageBox::warning(this,"Error", "HalfPeriod can't be 0",
                             QMessageBox::Cancel,
                             QMessageBox::Cancel);
        return;
    }

    int numbPoints = totalTime*60/halfPeriod+2;
    for(int i=0;i<numbPoints;i++)
    {
        timepoints << i*halfPeriod+firstTurnOnTime;
        if(i==0) timepointsDiff << firstTurnOnTime;
        else if(i<numbPoints-1) timepointsDiff << halfPeriod;

    }
    qDebug() << timepoints;
    qDebug() << timepointsDiff;
}
void myWidget::makeSinglePulseTimePoints()
{
    timepoints.clear();
    timepointsDiff.clear();

    timepoints << pulseStartTime;
    timepoints << pulseStopTime;
    timepointsDiff << pulseStartTime;
    timepointsDiff << pulseStopTime-pulseStartTime;

    qDebug() << timepoints;
    qDebug() << timepointsDiff;
}

void myWidget::runTask()
{
    if(timeIter.hasNext())
    {
        int currentNumb = timeIter.next();
        qDebug() << currentNumb;
        timer.setInterval(currentNumb*1000);
        timer.start();
    }
}

void myWidget::showRemaining()
{
    QString numb = QString::number(timer.remainingTime()/1000);
    m_ui->remainingTimeLabel->setText(QString("Next Switch in %1 seconds").arg(numb));
}

void myWidget::stopRun()
{
    timer.stop();
    queryTimer.stop();
    turnOff();
    m_ui->remainingTimeLabel->setText("Stopped");
}

void myWidget::openTimeFile()
{
    timeFileName = QFileDialog::getOpenFileName(this,
            "Open file that has time points", "/home/yanfei",
            "text file (*.txt)");
    qDebug() << timeFileName;

    QFile file(timeFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    timepoints.clear();
    while(!in.atEnd()) {
        QString line = in.readLine();
        timepoints << line.toInt();
    }
    file.close();
    isTimeSorted = isTimePointsSorted();
    if(!isTimeSorted)
    {
        QMessageBox::warning(this,"Error", "time points are not sorted",
                             QMessageBox::Cancel,
                             QMessageBox::Cancel);
    }
    else
    {
        timepointsDiff.clear();
        timepointsDiff << timepoints[0];
        for(int i=1;i<timepoints.length();i++)
        {
            timepointsDiff << timepoints[i] - timepoints[i-1];
        }
    }

}

bool myWidget::isTimePointsSorted()
{
    if(timepoints.length()<2) return true;
    int i = 1;
    qDebug() << timepoints.length();
    while((i<timepoints.length()) && (timepoints[i-1]<timepoints[i])) i++;
    if(i==timepoints.length()) return true;
    else return false;
}









































