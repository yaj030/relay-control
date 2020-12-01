#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include "relay.h"
#include <QList>
#include <QDialog>
#include "serialportdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort serialPort;
    bool serialPortReady;
    relay relays[4];
    serialPortDialog *serialDialog;
private slots:
};

#endif // MAINWINDOW
