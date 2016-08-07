#ifndef HYBRIDIMAGE_H
#define HYBRIDIMAGE_H
#include <QWidget>
#include <QImage>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>

using namespace cv;

class HybridImage: public QWidget
{
public:
    HybridImage();
    HybridImage(QImage src1, QImage src2);
    HybridImage(cv::Mat src1, cv::Mat src2);
    void setHighPassKsize(int size);
    void setLowPassKsize(int size);
    void setHighPassSigma(int sigma);
    void setLowPassSigma(int sigma);
    QImage Mat2QImage(const Mat& mat);
    Mat QImage2Mat(QImage image);
    QImage hybrid(Mat high_pass, Mat low_pass);
private:
    cv::Mat high_pass_source;
    cv::Mat low_pass_source;
    cv::Mat blend;


    QSlider* high_pass_kSize_slider;
    QSlider* low_pass_kSize_slider;
    QSlider* high_pass_sigma_slider;
    QSlider* low_pass_sigma_slider;

    int high_pass_kSize;
    int low_pass_kSize;
    float high_pass_sigma;
    float low_pass_sigma;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // HYBRIDIMAGE_H
