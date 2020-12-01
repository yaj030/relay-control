#include "serialportdialog.h"


serialPortDialog::serialPortDialog(QWidget* parent) : QDialog(parent)
{
    //QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    //QVBoxLayout* centralLayout = new QVBoxLayout(this); //better do it this way, instead of have a centralLayout member
    //setLayout(centralLayout);
    //centralLayout->addWidget(&serialListView);
    //serialSelectionModel = serialListView.selectionModel();
    //foreach (const QSerialPortInfo &info , infos) {
    //    QString s = info.portName() + " : "+ info.description() ;
    //    QStandardItem* serialPortItem = new QStandardItem(s);
    //    serialPortItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    //    serialListModel.appendRow(serialPortItem);
    //}
    //serialListView.setModel(&serialListModel);

    serialList = new QListWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(this); //better do it this way, instead of have a centralLayout member
    okButton = new QPushButton("OK",this);

    setLayout(centralLayout);
    centralLayout->addWidget(serialList);
    centralLayout->addWidget(okButton);

    //QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    infos = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info , infos) {
        QString s = info.portName() + " : "+ info.description() ;
        new QListWidgetItem(s, serialList);
    }

    connect(this->serialList, SIGNAL(currentRowChanged(int)), this, SLOT(getPortInfo(int)));
    connect(this->okButton, SIGNAL(clicked(bool)), this,SLOT(close()));
}

void serialPortDialog::getPortInfo(int rowNumb)
{
    info = infos[rowNumb];
}

QSerialPortInfo serialPortDialog::getInfo()
{
    return info;
}


