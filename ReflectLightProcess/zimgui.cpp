#include "zimgui.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>
ZImgUI::ZImgUI(qint32 iCh,QWidget *parent) : QWidget(parent)
{
    this->m_iCh=iCh;
    this->m_bFullScreen=false;
    this->m_iTsLast=QDateTime::currentDateTime().toMSecsSinceEpoch();
    this->m_iFrmTotal=0;
    this->m_iFps=0;
}
void ZImgUI::ZUpdateImg(const QImage &img)
{
    this->m_img=img;
    this->update();
}
void ZImgUI::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    ++this->m_iFrmTotal;
    qint64 iTsNow=QDateTime::currentDateTime().toMSecsSinceEpoch();
    //qDebug()<<this->m_iTsLast<<","<<iTsNow;
    if((iTsNow-this->m_iTsLast)>1000)
    {
        this->m_iFps=this->m_iFrmTotal;
        this->m_iFrmTotal=0;
        this->m_iTsLast=iTsNow;
    }
    QPainter painter(this);
    if(this->m_img.isNull())
    {
        painter.fillRect(QRectF(0,0,this->width(),this->height()),Qt::black);
        painter.setPen(QPen(Qt::red,3));
        QFont font=painter.font();
        font.setPixelSize(24);
        painter.setFont(font);
        painter.drawText(QRectF(0,0,300,100),QString("CH%1-NoSignal").arg(this->m_iCh));
        return;
    }

    painter.drawImage(QRectF(0,0,this->width(),this->height()),this->m_img);
    painter.setPen(QPen(Qt::green,3));
    QFont font=painter.font();
    font.setPixelSize(36);
    painter.setFont(font);
    painter.drawText(QRectF(0,0,300,100),QString("CH%1-%2").arg(this->m_iCh).arg(this->m_iFps));
}
void ZImgUI::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        if(this->m_bFullScreen)
        {
            this->m_bFullScreen=false;
            emit this->ZSigFullScreen(false);
        }else{
            this->m_bFullScreen=true;
            emit this->ZSigFullScreen(true);
        }
    }
    QWidget::mousePressEvent(event);
}
