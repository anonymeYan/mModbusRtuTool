#include "widget.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QFile qss_file(":/Ubuntu.qss");
//    if(!qss_file.open(QFile::ReadOnly))
//    {
//        qDebug()<<"qss file open error";
//    }
//    qApp->setStyleSheet(qss_file.readAll());
//    qss_file.close();
    Widget w;
    w.show();
    return a.exec();
}
