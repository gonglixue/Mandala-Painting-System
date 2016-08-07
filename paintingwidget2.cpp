#include "paintingwidget2.h"

Paintingwidget2::Paintingwidget2(QWidget *parent):QWidget(parent)
{
    resize(canvasWidth, canvasHeight);
    setWindowTitle(tr("template2"));
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background,QColor(0,0,0));
    palette.setColor(QPalette::WindowText, Qt::white);
    this->setPalette(palette);

}

void Paintingwidget2::paintEvent(QPaintEvent *)
{
    float PI = 3.1415;
    QPainter painter(this);
    painter.setPen(QPen(Qt::white));
    //draw the center image
    painter.save();
    painter.translate(t.center.x(),t.center.y());
    painter.drawImage(-(t.centerImage.width()/2), -(t.centerImage.height()/2),t.centerImage);
    painter.restore();

    // draw each level
    for(int i=0;i<4;i++)
    {
        painter.drawEllipse(t.center, t.r[i],t.r[i]);
    }

    // detail in level 4

    for(int i=0;i<t.numLevel[3];i++)
    {
        int cx,cy;
        double degree =  PI * (20 + i*360/8)/180.0;
        cx = t.center.x() + t.r[3]*cos(degree);
        cy = t.center.y() + t.r[3]*sin(degree);
        QPoint detailCenter(cx,cy);
        painter.drawEllipse(detailCenter,t.subRadiusLevel4,t.subRadiusLevel4);
    }
}
