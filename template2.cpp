#include "template2.h"

Template2::Template2()
{
    center = QPoint(600,350);

    for(int i=0;i<4;i++)
    {
        r[i] = (i+1)*50;
    }
    subRadiusLevel4 = 50;
    centerImage = QImage(":/tem2Image/center.png");
}

