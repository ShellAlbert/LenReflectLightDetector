#include "zmainui.h"
#include "zcapturethread.h"
#include "zmatfifo.h"
#include "zprocessingthread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ZMatFIFO fifoCap1(25,false);
    ZMatFIFO fifoCap2(25,false);
    ZMatFIFO fifoCap3(25,false);
    ZCaptureThread cap1("192.168.137.10",&fifoCap1);
    ZCaptureThread cap2("192.168.137.12",&fifoCap2);
    ZCaptureThread cap3("192.168.137.14",&fifoCap3);
    ZProcessingThread proc1(0,&fifoCap1);
    ZProcessingThread proc2(1,&fifoCap2);
    ZProcessingThread proc3(2,&fifoCap3);
    ZMainUI win;

    QObject::connect(&proc1,SIGNAL(ZSigNewImg(qint32,QImage)),&win,SLOT(ZSlotShowImg(qint32,QImage)));
    QObject::connect(&proc2,SIGNAL(ZSigNewImg(qint32,QImage)),&win,SLOT(ZSlotShowImg(qint32,QImage)));
    QObject::connect(&proc3,SIGNAL(ZSigNewImg(qint32,QImage)),&win,SLOT(ZSlotShowImg(qint32,QImage)));

    win.setMinimumSize(800,600);
    win.show();
    cap1.start();
    cap2.start();
    cap3.start();
    proc1.start();
    proc2.start();
    proc3.start();

    qint32 ret=app.exec();
    cap1.wait();
    cap2.wait();
    cap3.wait();
    proc1.wait();
    proc2.wait();
    proc3.wait();
    return ret;
}
