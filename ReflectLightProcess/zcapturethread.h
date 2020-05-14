#ifndef ZCAPTURETHREAD_H
#define ZCAPTURETHREAD_H

#include <QThread>
#include <QImage>
#include "zmatfifo.h"
class ZCaptureThread : public QThread
{
    Q_OBJECT
public:
    ZCaptureThread(ZMatFIFO *fifo);

signals:
    void ZSigFpsUpdated(qint32 iFps);
protected:
    void run();

private:
    qint32 getFps();
private:
    ZMatFIFO *m_fifo;
};

#endif // ZCAPTURETHREAD_H
