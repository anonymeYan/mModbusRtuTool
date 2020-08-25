#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setConnect();//连接自定义控件的信号与槽函数
    ui->spinBox_addr->setValue(1);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_com->addItem(serial.portName());
            serial.close();
        }
    }
    myModbusMaster = new modbusrtumaster();
    threadModbus   = new QThread();
    myModbusMaster->moveToThread(threadModbus);
    //    connect(threadModbus,SIGNAL(started()),myModbusMaster,SLOT(InitModbusMaster()));
    connect(threadModbus, &QThread::finished, myModbusMaster, &QObject::deleteLater);
    connect(threadModbus,&QThread::finished,threadModbus,&QObject::deleteLater);
    connect(this,SIGNAL(WriteSingleRegister(QString,int)),myModbusMaster,SLOT(WriteSingleRegister(QString,int)));
    connect(this,SIGNAL(InitModbusMaster(QString,int)),myModbusMaster,SLOT(InitModbusMaster(QString,int)));
    connect(myModbusMaster,SIGNAL(showMsg(QString)),this,SLOT(showMsg(QString)));
    connect(myModbusMaster,SIGNAL(sendData(QStringList)),this,SLOT(receiveData(QStringList)));


    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setConnect()
{
    connect( ui->lineEdit_1, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_2, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_3, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_4, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_5, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_6, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_7, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_8, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_9, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_10, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_11, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_12, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_13, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_14, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_15, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_16, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_17, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_18, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_19, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_20, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_21, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_22, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_23, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_24, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_25, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_26, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_27, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_28, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_29, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
    connect( ui->lineEdit_30, SIGNAL( clicked() ), this, SLOT(myLineEditClicked()) );
}


void Widget::on_btn_start_clicked()
{
    ui->btn_start->setText(QStringLiteral("运行中"));
    emit InitModbusMaster(ui->comboBox_com->currentText(),ui->spinBox_addr->value());
    threadModbus->start();
}

void Widget::showMsg(QString msg)
{
    ui->label_connect->setText(msg);
}

void Widget::receiveData(QStringList dataList)
{
    qDebug()<<QStringLiteral("receiveData");
    ui->lineEdit_1->setText(dataList.at(0));
    ui->lineEdit_2->setText(dataList.at(1));
    ui->lineEdit_3->setText(dataList.at(2));
    ui->lineEdit_4->setText(dataList.at(3));
    ui->lineEdit_5->setText(dataList.at(4));
    ui->lineEdit_6->setText(dataList.at(5));
    ui->lineEdit_7->setText(dataList.at(6));
    ui->lineEdit_8->setText(dataList.at(7));
    ui->lineEdit_9->setText(dataList.at(8));
    ui->lineEdit_10->setText(dataList.at(9));
    ui->lineEdit_11->setText(dataList.at(10));
    ui->lineEdit_12->setText(dataList.at(11));
    ui->lineEdit_13->setText(dataList.at(12));
    ui->lineEdit_14->setText(dataList.at(13));
    ui->lineEdit_15->setText(dataList.at(14));
    ui->lineEdit_16->setText(dataList.at(15));
    ui->lineEdit_17->setText(dataList.at(16));
    ui->lineEdit_18->setText(dataList.at(17));
    ui->lineEdit_19->setText(dataList.at(18));
    ui->lineEdit_20->setText(dataList.at(19));
    ui->lineEdit_21->setText(dataList.at(20));
    ui->lineEdit_22->setText(dataList.at(21));
    ui->lineEdit_23->setText(dataList.at(22));
    ui->lineEdit_24->setText(dataList.at(23));
    ui->lineEdit_25->setText(dataList.at(24));
    ui->lineEdit_26->setText(dataList.at(25));
    ui->lineEdit_27->setText(dataList.at(26));
    ui->lineEdit_28->setText(dataList.at(27));
    ui->lineEdit_29->setText(dataList.at(28));
    ui->lineEdit_30->setText(dataList.at(29));

}

void Widget::timerUpdate()
{
    qDebug()<<"mainwindow"<<QThread::currentThreadId();
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    QString timeLabel = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_DataTime->setText(str);
}

void Widget::myLineEditClicked()
{
    mylineedit *myLine = qobject_cast<mylineedit*>(sender());
    if(myLine == ui->lineEdit_1)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_1->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,0);
    }
    else if(myLine == ui->lineEdit_2)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_2->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,1);
    }
    else if(myLine == ui->lineEdit_3)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_3->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,2);
    }
    else if(myLine == ui->lineEdit_4)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_4->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,3);
    }
    else if(myLine == ui->lineEdit_5)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_5->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,4);
    }
    else if(myLine == ui->lineEdit_6)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_6->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,5);
    }
    else if(myLine == ui->lineEdit_7)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_7->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,6);
    }
    else if(myLine == ui->lineEdit_8)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_8->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,7);
    }
    else if(myLine == ui->lineEdit_9)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_9->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,8);
    }
    else if(myLine == ui->lineEdit_10)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_10->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,9);
    }
    else if(myLine == ui->lineEdit_11)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_11->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,10);
    }
    else if(myLine == ui->lineEdit_12)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_12->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,11);
    }
    else if(myLine == ui->lineEdit_13)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_13->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,12);
    }
    else if(myLine == ui->lineEdit_14)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_14->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,13);
    }
    else if(myLine == ui->lineEdit_15)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_15->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,14);
    }
    else if(myLine == ui->lineEdit_16)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_16->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,15);
    }
    else if(myLine == ui->lineEdit_17)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_17->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,16);
    }
    else if(myLine == ui->lineEdit_18)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_18->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,17);
    }
    else if(myLine == ui->lineEdit_19)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_19->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,18);
    }
    else if(myLine == ui->lineEdit_20)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_20->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,19);
    }
    else if(myLine == ui->lineEdit_21)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_21->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,20);
    }
    else if(myLine == ui->lineEdit_22)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_22->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,21);
    }
    else if(myLine == ui->lineEdit_23)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_23->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,22);
    }
    else if(myLine == ui->lineEdit_24)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_24->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,23);
    }
    else if(myLine == ui->lineEdit_25)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_25->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,24);
    }
    else if(myLine == ui->lineEdit_26)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_26->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,25);
    }
    else if(myLine == ui->lineEdit_27)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_27->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,26);
    }
    else if(myLine == ui->lineEdit_28)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_28->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,27);
    }
    else if(myLine == ui->lineEdit_29)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_29->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,28);
    }
    else if(myLine == ui->lineEdit_30)
    {
        bool ok;
        double value = QInputDialog::getDouble(this,tr("设置值"),tr("请输入0到1000之间的数值              "),
                                               0,-0,100000,1,&ok) ;
        if(ok)qDebug()<<"value = "<<value;
        ui->lineEdit_30->setText(QString::number(value));
        QString transData = QString::number(value);
        emit WriteSingleRegister(transData,29);
    }


}
