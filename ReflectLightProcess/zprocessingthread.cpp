#include "zprocessingthread.h"
#include "zgblpara.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "zmatfifo.h"
#include <QDebug>
ZProcessingThread::ZProcessingThread(ZMatFIFO *fifo)
{
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
        emit this->ZSigNewImg(0,img);

        cv::Mat matElement=cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,15));
        cv::Mat matOut;
        cv::dilate(mat,matOut,matElement);
        img=cvMat2QImage(matOut);
        emit this->ZSigNewImg(4,img);
#if 0
        cv::Mat mat01;
        cv::threshold(mat,mat01,200,255,CV_THRESH_BINARY);
        img=cvMat2QImage(mat01);
        emit this->ZSigNewImg(2,img);

        cv::Mat mat02;
        cv::threshold(mat,mat02,30,200.0,CV_THRESH_BINARY);
        img=cvMat2QImage(mat02);
        emit this->ZSigNewImg(3,img);

        cv::Mat mat03;
        cv::threshold(mat,mat03,50,200.0,CV_THRESH_BINARY);
        img=cvMat2QImage(mat03);
        emit this->ZSigNewImg(4,img);

        cv::Mat mat04;
        cv::threshold(mat,mat04,100,200.0,CV_THRESH_BINARY);
        img=cvMat2QImage(mat04);
        emit this->ZSigNewImg(5,img);
#endif
        this->usleep(100);
    }
}
