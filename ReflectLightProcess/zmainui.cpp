#include "zmainui.h"
#include "zgblpara.h"
#include <QDebug>
ZMainUI::ZMainUI(QWidget *parent)
    : QWidget(parent)
{
    for(qint32 i=0;i<9;i++)
    {
        this->m_llImg[i]=new ZImgUI(i+1);
        QObject::connect(this->m_llImg[i],SIGNAL(ZSigFullScreen(bool)),this,SLOT(ZSlotChFullScreen(bool)));
    }
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llImg[0],0,0,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[1],0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[2],0,2,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[3],1,0,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[4],1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[5],1,2,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[6],2,0,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[7],2,1,1,1);
    this->m_gridLayout->addWidget(this->m_llImg[8],2,2,1,1);
    this->setLayout(this->m_gridLayout);
}

ZMainUI::~ZMainUI()
{
    for(qint32 i=0;i<9;i++)
    {
        delete this->m_llImg[i];
    }
    delete this->m_gridLayout;
}
void ZMainUI::ZSlotShowImg(qint32 iCh,const QImage &img)
{
    if(iCh>=0 && iCh<=9)
    {
        this->m_llImg[iCh]->ZUpdateImg(img);
    }
}
void ZMainUI::ZSlotChFullScreen(bool bFullScreen)
{
    ZImgUI *ui=qobject_cast<ZImgUI*>(this->sender());
    if(bFullScreen)//single channel enter full screen mode.
    {
        QLayoutItem *item;
        while((item=this->m_gridLayout->takeAt(0))!=0)
        {
            if(item->widget())
            {
                item->widget()->setParent(NULL);
            }
        }
        this->m_gridLayout->addWidget(ui,0,0,1,1);
    }else{ //show 3x3 channels video.
        this->m_gridLayout->addWidget(this->m_llImg[0],0,0,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[1],0,1,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[2],0,2,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[3],1,0,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[4],1,1,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[5],1,2,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[6],2,0,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[7],2,1,1,1);
        this->m_gridLayout->addWidget(this->m_llImg[8],2,2,1,1);
    }
}
void ZMainUI::closeEvent(QCloseEvent *event)
{
    g_bExitFlag=true;
    QWidget::closeEvent(event);
}
