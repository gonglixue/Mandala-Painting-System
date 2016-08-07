#ifndef TEMPLATE1_H
#define TEMPLATE1_H
#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <QDebug>
class Template1
{
public:
    Template1();
    //QPoint center = (600,350);
    int r[5];
    int numOfLevel[5] = {12,12,8,24,64};
    int numOfDetail[5] { 12,12,32,32,64 };
    int detail_begin[5] = { 45,45,30,30,30 };
    int selfRotateOfLevel[5] = {0,0,0,0,0};
    int selfRotateOfDetail[5] = {0,0,0,0,0};
    int copyR,boarderID;
    QPixmap copyImage;


    QPoint center;

    QPixmap level[5];
    QPixmap level_origin[5];
    QPixmap level_origin_hsv[5];
    QPixmap detail[5];
    QPixmap detail_origin[5];
    void setNum_1(int num);
    void setNum_2(int num);
    void setNum_3(int num);
    void setNum_4(int num);
    void setNum_5(int num);

    void setNumOfLevel(int num);
    void setNumOfDetail(int num);
    void setCurrentLevelCtr(int i);
    void setCurrentDetailCtr(int i);
    void setDetailStart(int degree);
    int currentLevel();
    int currentDetail();
    void increaseRaduis(int step);
    void selfRotate();

private:
    int currentLevelCtr = 0;
    int currentDetailCtr = 0;
};

#endif // TEMPLATE1_H
