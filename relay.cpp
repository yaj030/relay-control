#include "relay.h"
#include <QThread>

QString relay::stringOn = "relay on 0\r";
QString relay::stringOff = "relay off 0\r";
QString relay::stringRead = "relay read 0\r";

relay::relay(QSerialPort &_serialPort, int _relayNumber):serialPort(&_serialPort),relayNumber(_relayNumber)
{
   setWritingStrings();
}

relay::relay()
{
}

void relay::setWritingStrings(){
    stringOn.replace(9,1,QString::number(relayNumber));
    writeDataOn = stringOn.toUtf8();

    stringOff.replace(10,1,QString::number(relayNumber));
    writeDataOff = stringOff.toUtf8();

    stringRead.replace(11,1,QString::number(relayNumber));
    writeDataRead = stringRead.toUtf8();
}


bool relay::getStatus(){
    serialPort->write(writeDataRead);
    QByteArray readData = serialPort->readAll();

    while (serialPort->waitForReadyRead(50))
           readData.append(serialPort->readAll());

    if (serialPort->error() == QSerialPort::ReadError) {
        qWarning() << QObject::tr("Failed to read from port %1, error: %2")
                  .arg(serialPort->portName()).arg(serialPort->errorString()) ;
    } else if (serialPort->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        qWarning() << QObject::tr("No data was currently available"
                                      " for reading from port %1")
                          .arg(serialPort->portName()) ;
    }

    QString str_o = QString::fromUtf8(readData);
    if(str_o.length() == 20){
        return false;
    }
    else if (str_o.length() == 19){
        return true;
    }
    else {
        qDebug() << str_o;
        qDebug() << str_o.length();
        return false;
    }
}

int relay::getRelayNumber(){
    return relayNumber;
}
void relay::setRelayNumber(int number){
    relayNumber = number;
    setWritingStrings();
}

QString relay::getPortName(){
    return serialPort->portName();
}
void relay::setPort(QSerialPort *port){
    serialPort = port;
}

bool relay::turnOff(){
    const qint64 bytesWritten = serialPort->write(writeDataOff);
    if (bytesWritten == -1) {
           qWarning() << QObject::tr("Failed to write the data to port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       } else if (bytesWritten != writeDataOff.size()) {
           qWarning() << QObject::tr("Failed to write all the data to port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       } else if (!serialPort->waitForBytesWritten(5000)) {
           qWarning() << QObject::tr("Operation timed out or an error "
                                         "occurred for port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       }

    QByteArray readData = serialPort->readAll();
    while (serialPort->waitForReadyRead(50))
           readData.append(serialPort->readAll());

    if (!getStatus()){
        qDebug() << "turned off";
        return 1;
    }
    else{
        return 0;
    }
}

bool relay::turnOn(){

    const qint64 bytesWritten = serialPort->write(writeDataOn);
    if (bytesWritten == -1) {
           qWarning() << QObject::tr("Failed to write the data to port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       } else if (bytesWritten != writeDataOn.size()) {
           qWarning() << QObject::tr("Failed to write all the data to port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       } else if (!serialPort->waitForBytesWritten(5000)) {
           qWarning() << QObject::tr("Operation timed out or an error "
                                         "occurred for port %1, error: %2")
                             .arg(serialPort->portName()).arg(serialPort->errorString()) ;
       }

    QByteArray readData = serialPort->readAll();
    while (serialPort->waitForReadyRead(50))
           readData.append(serialPort->readAll());

    if (getStatus()){
        qDebug() << "turned on";
        return 1;
    }
    else{
        return 0;
    }
}


