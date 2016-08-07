#ifndef PAINTINGWIDGET_H
#define PAINTINGWIDGET_H
#include "mainwindow.h"
#include <QWidget>
#include <QPainter>
#include "template1.h"
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "hybridimage.h"
using namespace cv;
class PaintingWidget : public QWidget
{
    Q_OBJECT
public:
    PaintingWidget(QWidget *parent = 0);
    int canvasWidth = 1300;
    int canvasHeight = 700;
    Template1 t;
    QLabel* label1;
    //void painting(QPainter painter);
    void updatepainting();
    void animationCtr();
    void radiationCTR();
    void setNumOfLevel(int i);
    void setCurrentLevel(int i);
    void loadImage();
    void loadDetail();
    void setCurrentDetail(int i);
    void setNumOfDetail(int i);
    void setStartOfDetail(int degree);
    void setTemplateRadius(int step);
    void setSelfRotateOfLevel(int degree);
    void setSelfRotateOfDetail(int degree);
    void setR(int r);
    void setDetailSize(int s);
    void setLevelSize(int s);
    void setAnimationSpeed(int t);
    QImage Mat2QImage(const cv::Mat &mat);
    QPixmap Mat2QPixmap(const cv::Mat &mat);
    cv::Mat QImage2Mat(QImage image);
    cv::Mat QPixmap2Mat(QPixmap qpix);
    void renderCanvas();
    void renderCanvas2();
    void newBlend();
    //cv::Mat hybridImage(Mat src1, Mat src2);
    void adjustHsvHue(int h);
    void adjustHsvSaturation(int s);
    void adjustHsvValue(int v);
    QImage adjustQImageHSV(QImage input);
    void adjustCurrentHSV();
    void adjustAlpha(int alpha);
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    //QPainter painter;
    int rotateAngle = 60;
    int step = 0;
    int radiusStep = 0;
    bool bAnimation = false;
    bool bRadiation = false;
    bool bRenderCanvas = false;

    QPushButton* animationBtn;

    //QSlider* whichLevelSlider;
    QComboBox* whichLevelBox;
    QSlider* numOfLevelSlider;
    QSlider* levelRotateSlider;
    QSlider* setLevelRSlider;
    QSlider* levelSizeSlider;
    QPushButton* loadImageBtn;

    QComboBox* whichDetailBox;
    QSlider* numOfDetailSlider;
    QSlider* detailAngleSlider;
    QSlider* detailRotateSlider;
    QSlider* detailSizeSlider;

    QPushButton* radiationAnimateBtn;
    QPushButton* loadDetailImageBtn;

    QSlider* speedSlider;

    QLabel* whichLevelLabel;
    QLabel* numOfLevelLabel;
    QLabel* levelSelfRotateLabel;
    QLabel* setLevelRLabel;
    QLabel* levelSizeLabel;

    QLabel* whichDetailLabel;
    QLabel* numOfDetaiLabel;
    QLabel* detailAngleLabel;
    QLabel* detailSelfRotateLabel;
    QLabel* detailSizeLabel;
    QLabel* speedLabel;


    QTimer* timer;

    bool dragStart = false;
    int startLevel = -1;

    QPixmap canvas;

    QPushButton* render1Btn;
    QPushButton* render2Btn;
    QPushButton* blendBtn;
    cv::Mat render1;
    cv::Mat render2;
    HybridImage* hybridWidget;


    QSlider* hueSlider;
    QSlider* saturationSlider;
    QSlider* valueSlider;
    QLabel* hueLabel;
    QLabel* saturationLabel;
    QLabel* valueLabel;
    int hsv_h;
    int hsv_s;
    int hsv_v;

    QSlider* alphaSlider;

};



#endif // PAINTINGWIDGET_H
