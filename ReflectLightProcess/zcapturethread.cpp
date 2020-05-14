#include "zcapturethread.h"
#include "zgblpara.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <QDebug>
#include <QTime>
ZCaptureThread::ZCaptureThread(ZMatFIFO *fifo)
{
    this->m_fifo=fifo;
}
void ZCaptureThread::run()
{
    cv::VideoCapture cap;
    while(!g_bExitFlag)
    {
        if(!cap.isOpened())
        {
            qDebug()<<"connection lost!";
            if(cap.open("rtsp://192.168.137.10:554/user=admin&password=&channel=1&stream=0.sdp?real_stream"))
            {
                double dRate=cap.get(CV_CAP_PROP_FPS);
                qDebug()<<"rate:"<<dRate;
            }else{
                qDebug()<<"open rtsp failed.";
                this->sleep(5);
                continue;
            }
        }
        cv::Mat  mat;
        cap>>mat;
        if(!mat.data)
        {
            qDebug()<<"failed to get rtsp!";
            cap.release();
            this->sleep(5);
            continue;
        }
        this->m_fifo->ZAddFrame(mat);
        this->usleep(1000);
    }
    cap.release();
}
qint32 ZCaptureThread::getFps()
{
    static QTime time;
    static bool bStarted=false;
    static qint32 iFrameCount=0;
    qint32 iFps=0;
    if(!bStarted)
    {
        bStarted=true;
        time.start();
    }
    if(time.elapsed()>1000)
    {
        iFps=iFrameCount*1000/time.elapsed();
        iFrameCount=0;
    }else{
        ++iFrameCount;
    }
    return iFps;
}
