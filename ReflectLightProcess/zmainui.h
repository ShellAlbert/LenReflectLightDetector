#ifndef ZMAINUI_H
#define ZMAINUI_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QImage>
#include <QList>
#include "zimgui.h"

class ZMainUI : public QWidget
{
    Q_OBJECT

public:
    ZMainUI(QWidget *parent = 0);
    ~ZMainUI();

public slots:
    void ZSlotShowImg(qint32 iWhich,const QImage &img);
private slots:
    void ZSlotChFullScreen(bool bFullScreen);
protected:
    void closeEvent(QCloseEvent *event);
private:
    ZImgUI *m_llImg[9];
    QGridLayout *m_gridLayout;

};

#endif // ZMAINUI_H
