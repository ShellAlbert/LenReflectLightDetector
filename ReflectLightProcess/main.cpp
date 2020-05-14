#include "zmainui.h"
#include "zcapturethread.h"
#include "zmatfifo.h"
#include "zprocessingthread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ZMatFIFO fifo(25,false);
    ZCaptureThread capture(&fifo);
    ZProcessingThread process(&fifo);
    ZMainUI win;

    QObject::connect(&process,SIGNAL(ZSigNewImg(qint32,QImage)),&win,SLOT(ZSlotShowImg(qint32,QImage)));

    win.setMinimumSize(800,600);
    win.show();
    capture.start();
    process.start();

    qint32 ret=app.exec();
    capture.wait();
    process.wait();
    return ret;
}
