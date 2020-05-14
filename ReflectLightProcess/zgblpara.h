#ifndef ZGBLPARA_H
#define ZGBLPARA_H

#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

extern bool g_bExitFlag;

extern QImage cvMat2QImage(const cv::Mat &mat);
extern int getFps();
#endif // ZGBLPARA_H
