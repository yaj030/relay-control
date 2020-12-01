#ifndef RELAY_H
#define RELAY_H
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QString>

class relay
{
public:
    explicit relay(QSerialPort &_serialPort, int _relayNumber);
    explicit relay();
    bool turnOn();
    bool turnOff();
    bool getStatus();
    QString getPortName();
    int getRelayNumber();
    void setRelayNumber(int number);
    void setPort(QSerialPort *port);

private:
    QSerialPort * serialPort;
    int relayNumber;
    static QString stringOn;
    static QString stringOff;
    static QString stringRead; // another way is const static QString stringOn = "relay on 0\r" without definition in the .cpp file
    QByteArray writeDataOn;
    QByteArray writeDataOff;
    QByteArray writeDataRead;
    void setWritingStrings();
};

#endif // RELAY_H
