#include "hybridimage.h"

HybridImage::HybridImage()
{

}

QImage HybridImage::Mat2QImage(const Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

Mat HybridImage::QImage2Mat(QImage image)
{
     cv::Mat mat;
     qDebug() << image.format();
     switch(image.format())
     {
     case QImage::Format_ARGB32:
     case QImage::Format_RGB32:
     case QImage::Format_ARGB32_Premultiplied:
         mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
         break;
     case QImage::Format_RGB888:
         mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
         cv::cvtColor(mat, mat, CV_BGR2RGB);
         break;
     case QImage::Format_Indexed8:
         mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
         break;
     }
     return mat;
}

HybridImage::HybridImage(QImage src1, QImage src2)
{
    high_pass_source = QImage2Mat(src1);
    low_pass_source = QImage2Mat(src2);
    high_pass_kSize = 15;
    low_pass_kSize = 7;
    high_pass_sigma = 1.0f;
    low_pass_sigma = 30.0f;
}

HybridImage::HybridImage(Mat src1, Mat src2)
{
    resize(1300,700);

    high_pass_source = src1;
    low_pass_source = src2;
    high_pass_kSize = low_pass_kSize = 7;
    high_pass_sigma = low_pass_sigma = 0.8f;

    high_pass_kSize_slider = new QSlider(Qt::Horizontal);
    high_pass_kSize_slider->setMinimum(0);
    high_pass_kSize_slider->setMaximum(100);
    QObject::connect(high_pass_kSize_slider,&QSlider::valueChanged, this, &HybridImage::setHighPassKsize);

    low_pass_kSize_slider = new QSlider(Qt::Horizontal);
    low_pass_kSize_slider->setMinimum(0);
    low_pass_kSize_slider->setMaximum(100);
    QObject::connect(low_pass_kSize_slider, &QSlider::valueChanged, this, &HybridImage::setLowPassKsize);

    high_pass_sigma_slider = new QSlider(Qt::Horizontal);
    high_pass_sigma_slider->setMinimum(0);
    high_pass_sigma_slider->setMaximum(1000);
    QObject::connect(high_pass_kSize_slider, &QSlider::valueChanged, this, &HybridImage::setHighPassSigma);


    low_pass_sigma_slider = new QSlider(Qt::Horizontal);
    low_pass_sigma_slider->setMinimum(0);
    low_pass_sigma_slider->setMaximum(1000);
    QObject::connect(low_pass_sigma_slider, &QSlider::valueChanged, this, &HybridImage::setLowPassSigma);

    QVBoxLayout* ctrLayout = new QVBoxLayout();
    ctrLayout->addWidget(high_pass_kSize_slider);
    ctrLayout->addWidget(low_pass_kSize_slider);
    ctrLayout->addWidget(high_pass_sigma_slider);
    ctrLayout->addWidget(low_pass_sigma_slider);
    QVBoxLayout* empty = new QVBoxLayout();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(empty);
    mainLayout->addLayout(ctrLayout);
    mainLayout->setStretchFactor(empty, 10);
    mainLayout->setStretchFactor(ctrLayout,3);
    this->setLayout(mainLayout);
}

QImage HybridImage::hybrid(Mat high_pass, Mat low_pass)
{
    qDebug() << "hybrid()";
    // low pass
    cv::GaussianBlur(low_pass, low_pass, cv::Size(low_pass_kSize, low_pass_kSize), low_pass_sigma);

    // high pass
    Mat subtractImg;
    Mat low2;
    cv::GaussianBlur(high_pass,low2,cv::Size(high_pass_kSize, high_pass_kSize), high_pass_sigma);
    cv::subtract(high_pass,low2, subtractImg);
    Mat addImg(subtractImg.rows, subtractImg.cols, subtractImg.type(), cv::Scalar(128,128,128));
    subtractImg = subtractImg + addImg;
    imshow("subtract", subtractImg);

    addWeighted(low_pass, 0.5, subtractImg, 0.5, 0.0, blend);
    imshow("blend", blend);

    QImage result = Mat2QImage(blend);
    result.save("hybridimage.jpg");
    return result;

}

void HybridImage::paintEvent(QPaintEvent *)
{
    qDebug() << "hybridImage::paintEvent" ;
    QPainter painter(this);
    QImage BlendQimg = hybrid(high_pass_source, low_pass_source);
    painter.drawImage(0,0,BlendQimg);
}

void HybridImage::setHighPassKsize(int size)
{
    high_pass_kSize = 2*size + 1;
    update();
}
void HybridImage::setLowPassKsize(int size)
{
    low_pass_kSize = 2*size + 1;
    update();
}
void HybridImage::setHighPassSigma(int sigma)
{
    high_pass_sigma = sigma / 100.0;
    update();
}
void HybridImage::setLowPassSigma(int sigma)
{
    low_pass_sigma = sigma / 100.0;
    update();
}

