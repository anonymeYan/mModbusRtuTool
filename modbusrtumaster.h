#ifndef MODBUSRTUMASTER_H
#define MODBUSRTUMASTER_H

#include <QObject>
#include "QDebug"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qmodbusrtuserialmaster.h>
#include <QThread>
#include <QEventLoop>

class modbusrtumaster : public QObject
{
    Q_OBJECT
public:
    explicit modbusrtumaster(QObject *parent = nullptr);
    void Delay_MSec(unsigned int msec);

signals:
    void showMsg(QString msg);
    void sendData(QStringList data);

private:
    QModbusClient *modbusDevice;
    QTimer *timerReadModbus ;
    QString comPortName;
    int serverAddress = 1 ;

    int startAddress = 0;    //读取modbus变量起始地址
    int numOfEntries = 30;   //读取modbus变量的数量
    QStringList dataList;

private slots:
    void InitModbusMaster(QString comPortName,int address);
    void timerReadUpdate(void);
    void readReady(void);
    void WriteSingleRegister(QString data,int address);


};

#endif // MODBUSRTUMASTER_H
