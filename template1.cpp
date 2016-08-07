#include "template1.h"
#include <QString>
#include "paintingwidget.h"
#include <QDir>
Template1::Template1()
{
   center.setX(500);
   center.setY(350);
   QString path=QDir::currentPath();
   qDebug() << path + "/flower2.png";


   level[0].load(path + "/template1/flower2.png");
   level[1].load(path + "/template1/flower3.png");
   level[2].load(path + "/template1/flower2.png");
   level[3].load(path + "/template1/flower4.png");
   level[4].load(path + "/template1/0.png");
   for(int i=0;i<5;i++)
   {
       level_origin[i] = level[i];
       level_origin_hsv[i] = level[i];
   }
   //for(int i=0;i<5;i++)
       detail[1].load(path + "/template1/detail1.png");


   r[0] = 50;
   r[1] = 100;
   r[2] = 150;
   r[3] = 200;
   r[4] = 250;
   copyR = r[4];
   boarderID = 4;

}

void Template1::setNum_1(int num)
{
    numOfLevel[0] = num;
}
void Template1::setNum_2(int num)
{
    numOfLevel[1] = num;
}
void Template1::setNum_3(int num)
{
    numOfLevel[2] = num;
}
void Template1::setNum_4(int num)
{
    numOfLevel[3] = num;
}
void Template1::setNum_5(int num)
{
    numOfLevel[4] = num;
}
void Template1::setNumOfLevel(int num)
{
    numOfLevel[currentLevelCtr] = num;
}
void Template1::setCurrentLevelCtr(int i)
{
    currentLevelCtr = i;
}

int Template1::currentLevel()
{
    return currentLevelCtr;
}
void Template1::setCurrentDetailCtr(int i)
{
    currentDetailCtr = i;
}
int Template1::currentDetail()
{
    return currentDetailCtr;
}
void Template1::setNumOfDetail(int num)
{
    numOfDetail[currentDetailCtr] = num;
}
void Template1::setDetailStart(int degree)
{
    detail_begin[currentDetailCtr] = degree;
}
void Template1::increaseRaduis(int step)
{
    for(int i=0;i<5;i++)
    {
        r[i] = r[i] + step;
        if(r[i] > 260)
        {
            copyR = r[i];
            r[i] = 0;

            boarderID = i;
        }
    }
    copyR += step;
}
void Template1::selfRotate()
{
    for(int i=0;i<5;i++)
    {
        QMatrix rotateM;
        rotateM.rotate(selfRotateOfLevel[i]);
        int w,h;
        w = level[i].width();
        h = level[i].height();


        level[i] = level_origin_hsv[i].transformed(rotateM,Qt::SmoothTransformation);
        level[i] = level[i].scaled(w,h,Qt::IgnoreAspectRatio);

        QMatrix rotateM2;
        rotateM2.rotate(selfRotateOfDetail[i]);
        w = detail[i].width();
        h = detail[i].height();
        detail[i] = detail_origin[i].transformed(rotateM2,Qt::SmoothTransformation);
        detail[i] = detail[i].scaled(w,h,Qt::IgnoreAspectRatio);
    }
}
