#ifndef ZIMGUI_H
#define ZIMGUI_H

#include <QWidget>
#include <QImage>
#include <QTime>
class ZImgUI : public QWidget
{
    Q_OBJECT
public:
    explicit ZImgUI(qint32 iCh,QWidget *parent = 0);
    void ZUpdateImg(const QImage &img);
signals:
    void ZSigFullScreen(bool bFullScreen);
public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
private:
    qint32 m_iCh;
    QImage m_img;
    bool m_bFullScreen;
private:
    //for calculate flush fps.
    qint64 m_iTsLast;
    qint32 m_iFrmTotal;
    qint32 m_iFps;
};

#endif // ZIMGUI_H
