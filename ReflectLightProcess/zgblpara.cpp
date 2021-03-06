#include "zgblpara.h"
#include <QTime>
#include <QDebug>
bool g_bExitFlag=false;

QImage cvMat2QImage(const cv::Mat &mat)
{
    if(mat.type()==CV_8UC1)
    {
        QVector<QRgb> colorTable;
        for(int i=0;i<256;i++)
        {
            colorTable.push_back((qRgb(i,i,i)));
        }
        const uchar *qImageBuffer=(const uchar*)mat.data;
        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    if(mat.type()==CV_8UC3)
    {
        //copy input Mat.
        const uchar *qImageBuffer=(const uchar*)mat.data;
        //create QImage with same dimensions as input Mat.
        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
        return img.rgbSwapped();
    }else{
        qDebug()<<"ERROR:Mat could not be converted to QImage.";
        return QImage();
    }
}

