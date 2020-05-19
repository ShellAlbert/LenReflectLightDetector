#ifndef ZPROCESSINGTHREAD_H
#define ZPROCESSINGTHREAD_H

#include <QThread>
#include <QImage>
class ZMatFIFO;
class ZProcessingThread : public QThread
{
    Q_OBJECT
public:
    ZProcessingThread(qint32 index,ZMatFIFO *fifo);
signals:
    void ZSigNewImg(qint32 iWhich,const QImage &img);
protected:
    void run();
private:
    qint32 m_index;
    ZMatFIFO *m_fifo;
};

#endif // ZPROCESSINGTHREAD_H
