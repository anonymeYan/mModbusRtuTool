#include "modbusrtumaster.h"






modbusrtumaster::modbusrtumaster(QObject *parent) : QObject(parent)
{

}

void modbusrtumaster::Delay_MSec(unsigned int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}





void modbusrtumaster::InitModbusMaster(QString comPortName,int address)
{
    qDebug()<<QStringLiteral("InitModbusMaster")<<QThread::currentThreadId();

    serverAddress=address;

    modbusDevice = new QModbusRtuSerialMaster(this);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                         comPortName);//获取串口端口,下面设置各种参数
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                         "N");//无较验
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                         "9600");//波特率为9600
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                         "8");//数据位为8位
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                         "1");//停止位为1位
    modbusDevice->setTimeout(1000);//连接超时1S
    modbusDevice->setNumberOfRetries(3);//连接失败重试三次连接

    timerReadModbus = new QTimer();
    connect(timerReadModbus,SIGNAL(timeout()),this,SLOT(timerReadUpdate()));

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {//如果处在非连接状态，进行连接//进行连接
        if (!modbusDevice->connectDevice())
        {//连接失败
            emit showMsg(QStringLiteral("连接失败"));
        }
        else{//连接成功
            emit showMsg(QStringLiteral("初始化"));
            timerReadModbus->start(1000);
        }
    }
    else{//已经处在连接状态进行断开连接的操作
        emit showMsg(QStringLiteral("初始化"));
        timerReadModbus->start(1000);
    }

    for(int i=0;i<30;i++)
        dataList.append("null");
}





void modbusrtumaster::timerReadUpdate()
{
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug()<<"timerReadUpdate Read Error:"<<"Modbus Device is not connected!"<<modbusDevice->errorString();
        emit showMsg(QStringLiteral("未连接"));
        return;
    }

    //读取modbus变量起始地址
    startAddress = 0;
    //读取modbus变量的数量
    numOfEntries = 30;
    quint16 numE=static_cast<quint16>(numOfEntries);

    QModbusDataUnit dataunit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, startAddress, numE);
    if(auto *reply = modbusDevice->sendReadRequest( dataunit, serverAddress)){
        if(!reply->isFinished()) {
            qDebug()<<"read HoldingRegisters"<<QThread::currentThreadId();
            connect(reply, &QModbusReply::finished, this, &modbusrtumaster::readReady);
        } else {
            delete reply;
        }
    }else{
        qDebug()<<"Read Error1:"<<modbusDevice->errorString();
        emit showMsg(QStringLiteral("通讯错误"));
    }
}


void modbusrtumaster::readReady()
{
    qDebug()<<"read ready"<<QThread::currentThreadId();
    auto reply = qobject_cast<QModbusReply *> (sender());
    if (!reply) return;
    if (reply->error() == QModbusDevice::NoError) {
        emit showMsg(QStringLiteral("通讯中..."));
        const QModbusDataUnit unit = reply->result();

        dataList.clear();
        for(int i=0;i<30;i++)
            dataList.append("null");

        dataList.replace(0,QString::number(unit.value(0)));
        dataList.replace(1,QString::number(unit.value(1)));
        dataList.replace(2,QString::number(unit.value(2)));
        dataList.replace(3,QString::number(unit.value(3)));
        dataList.replace(4,QString::number(unit.value(4)));
        dataList.replace(5,QString::number(unit.value(5)));
        dataList.replace(6,QString::number(unit.value(6)));
        dataList.replace(7,QString::number(unit.value(7)));
        dataList.replace(8,QString::number(unit.value(8)));
        dataList.replace(9,QString::number(unit.value(9)));
        dataList.replace(10,QString::number(unit.value(10)));
        dataList.replace(11,QString::number(unit.value(11)));
        dataList.replace(12,QString::number(unit.value(12)));
        dataList.replace(13,QString::number(unit.value(13)));
        dataList.replace(14,QString::number(unit.value(14)));
        dataList.replace(15,QString::number(unit.value(15)));
        dataList.replace(16,QString::number(unit.value(16)));
        dataList.replace(17,QString::number(unit.value(17)));
        dataList.replace(18,QString::number(unit.value(18)));
        dataList.replace(19,QString::number(unit.value(19)));
        dataList.replace(20,QString::number(unit.value(20)));
        dataList.replace(21,QString::number(unit.value(21)));
        dataList.replace(22,QString::number(unit.value(22)));
        dataList.replace(23,QString::number(unit.value(23)));
        dataList.replace(24,QString::number(unit.value(24)));
        dataList.replace(25,QString::number(unit.value(25)));
        dataList.replace(26,QString::number(unit.value(26)));
        dataList.replace(27,QString::number(unit.value(27)));
        dataList.replace(28,QString::number(unit.value(28)));
        dataList.replace(29,QString::number(unit.value(29)));

        //        //先替换后面的，再替换前面的，顺序会出错
        //        qDebug()<<dataList.size();
        //        qDebug()<<dataList;
        //        qDebug()<<dataList.indexOf("103");
        emit sendData(dataList);

    } else if (reply->error() == QModbusDevice::ProtocolError) {
        emit showMsg("ProtocolError");
    } else {
        emit showMsg(reply->errorString());
    }

}



void modbusrtumaster::WriteSingleRegister(QString data, int address)
{
    qDebug("WriteSingleRegister address:%d ",address);
    if(!modbusDevice || modbusDevice ->state() != QModbusDevice::ConnectedState) {
        qDebug("Modbus Device is not connected!");
        emit showMsg("Modbus Device is not connected!");
        return;
    }
    QModbusDataUnit writeUnit = QModbusDataUnit( QModbusDataUnit::HoldingRegisters,address,1);
    writeUnit.setValue(0,data.toUShort());
    if(auto *reply = modbusDevice->sendWriteRequest(writeUnit, serverAddress)){
        if(!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if(reply->error() == QModbusDevice::ProtocolError){
                    emit showMsg(reply->errorString());
                }else if(reply->error() != QModbusDevice::NoError){
                    emit showMsg(reply->errorString());
                }
                reply->deleteLater();
            });
        }else{
            emit showMsg(reply->errorString());
        }
    }
}








