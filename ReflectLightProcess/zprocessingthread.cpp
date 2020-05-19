#include "zprocessingthread.h"
#include "zgblpara.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "zmatfifo.h"
#include <QDebug>
ZProcessingThread::ZProcessingThread(qint32 index,ZMatFIFO *fifo)
{
    this->m_index=index;
    this->m_fifo=fifo;
}
void ZProcessingThread::run()
{
    QImage img;
    while(!g_bExitFlag)
    {
        cv::Mat mat=this->m_fifo->ZGetFrame();
        cv::cvtColor(mat,mat,cv::COLOR_RGB2GRAY);

        img=cvMat2QImage(mat);
        switch(this->m_index)
        {
        case 0:
            emit this->ZSigNewImg(0,img);
            break;
        case 1:
            emit this->ZSigNewImg(1,img);
            break;
        case 2:
            emit this->ZSigNewImg(2,img);
            break;
        default:
            break;
        }


        cv::Mat matElement=cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,15));
        cv::Mat matOut;
        cv::dilate(mat,matOut,matElement);
        img=cvMat2QImage(matOut);
        switch(this->m_index)
        {
        case 0:
            emit this->ZSigNewImg(3,img);
            break;
        case 1:
            emit this->ZSigNewImg(4,img);
            break;
        case 2:
            emit this->ZSigNewImg(5,img);
            break;
        default:
            break;
        }


        cv::Mat mat01;
        cv::threshold(matOut,mat01,180,255,CV_THRESH_BINARY);
        img=cvMat2QImage(mat01);
        switch(this->m_index)
        {
        case 0:
            emit this->ZSigNewImg(6,img);
            break;
        case 1:
            emit this->ZSigNewImg(7,img);
            break;
        case 2:
            emit this->ZSigNewImg(8,img);
            break;
        default:
            break;
        }
        this->usleep(100);
    }
}
