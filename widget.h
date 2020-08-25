#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "modbusrtumaster.h"
#include "mylineedit.h"
#include <qinputdialog.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setConnect();
signals:
    void InitModbusMaster(QString comPortName,int address);
    void WriteSingleRegister(QString data,int address);


private slots:
    void on_btn_start_clicked();
    void showMsg(QString msg);
    void receiveData(QStringList dataList);
    void timerUpdate();
    void myLineEditClicked();

private:
    Ui::Widget *ui;
    QTimer *timer;
    modbusrtumaster* myModbusMaster;
    QThread*  threadModbus;
};
#endif // WIDGET_H
