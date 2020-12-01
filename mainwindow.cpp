#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "relay.h"
#include <QThread>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    serialDialog = new serialPortDialog(this);
    //serialDialog->showFullScreen();
    serialDialog->exec();

   // QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
   // serialPort.setPort(infos[0]); // this is essential
    serialPort.setPort(serialDialog->getInfo());

    if (!serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << QObject::tr("Failed to open port %1, error: %2").arg(serialPort.portName()).arg(serialPort.error()) ;
    }
    else  ui->setupUi(this);
    for(int i=0;i<4;i++)
    {
        relays[i].setRelayNumber(i);
        relays[i].setPort(&serialPort);
    }

    ui->widget0->setRelay(relays);
    ui->widget0->updateStatus();
    ui->widget1->setRelay(relays+1);
    ui->widget1->updateStatus();


}

MainWindow::~MainWindow()
{
    delete ui;
}


