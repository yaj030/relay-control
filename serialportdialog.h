#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H
#include <QDialog>
#include <QtGui>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>

class serialPortDialog : public QDialog
{
    Q_OBJECT
public:
    explicit serialPortDialog(QWidget* parent = 0);
    QSerialPortInfo getInfo();


//private:
//    QListView serialListView;
//    QStandardItemModel serialListModel;
//    QItemSelectionModel* serialSelectionModel;
//    //QSerialPortInfo info;
//private slots:
//    int getRow();

private:
    QListWidget* serialList;
    QPushButton* okButton;
    QSerialPortInfo info;
    QList<QSerialPortInfo> infos;
private slots:
    void getPortInfo(int rowNumb);



};


#endif // SERIALPORTDIALOG_H
