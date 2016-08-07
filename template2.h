#ifndef TEMPLATE2_H
#define TEMPLATE2_H

#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QtMath>
class Template2
{
public:
    Template2();
    QPoint center;
    int r[4];
    int numLevel[4] = {8, 32, 16, 8};
    int subRadiusLevel4;
    int numSubCircleLevel4=7;

    QImage level[4];
    QImage detailLevel4;
    QImage centerImage;


};

#endif // TEMPLATE2_H
