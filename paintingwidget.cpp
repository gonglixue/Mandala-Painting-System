#include "paintingwidget.h"
#include <QPalette>
#include <QtMath>
#include <QString>
PaintingWidget::PaintingWidget(QWidget *parent):QWidget(parent)
{
   resize(canvasWidth,canvasHeight);
   setWindowTitle(tr("Mantuoluo"));
   //this->setParent(parent);
   this->setAutoFillBackground(true);

   QPalette palette;
   palette.setColor(QPalette::Background, QColor(0,0,0));
   palette.setColor(QPalette::WindowText,Qt::white);
   this->setPalette(palette);

   /*label1 = new QLabel(this);
   Mat mat = imread("f:/gonglixue.jpg");
   imshow("mat",mat);
   QPixmap test = Mat2QPixmap(mat);
   label1->setPixmap(test);
   label1->setAlignment(Qt::AlignBottom);
   label1->show();*/

   animationBtn = new QPushButton("animat");
   QObject::connect(animationBtn, &QPushButton::clicked, this,&PaintingWidget::animationCtr);
   numOfLevelSlider = new QSlider(Qt::Horizontal);
   numOfLevelSlider->setMinimum(0);
   numOfLevelSlider->setMaximum(64);
   numOfLevelSlider->setValue(8);
   QObject::connect(numOfLevelSlider,&QSlider::valueChanged,this,&PaintingWidget::setNumOfLevel);
   /*whichLevelSlider = new QSlider(Qt::Horizontal);
   whichLevelSlider->setMinimum(0);
   whichLevelSlider->setMaximum(4);
   whichLevelSlider->setValue(0);
   QObject::connect(whichLevelSlider,&QSlider::valueChanged,this,&PaintingWidget::setCurrentLevel);*/
   whichLevelBox = new QComboBox();
   for(int i=0;i<5;i++)
   {
       whichLevelBox->insertItem(i,QString::number(i));
   }
   void(QComboBox::*fp)(int)=&QComboBox::currentIndexChanged;
   QObject::connect(whichLevelBox,fp,this,&PaintingWidget::setCurrentLevel);
   loadImageBtn = new QPushButton("Load Texture");
   QObject::connect(loadImageBtn,&QPushButton::clicked,this,&PaintingWidget::loadImage);
    // detail
   whichDetailBox = new QComboBox();
   for(int i=0;i<5;i++)
   {
       whichDetailBox->insertItem(i,QString::number(i));
   }
   void(QComboBox::*fpDetail)(int) = &QComboBox::currentIndexChanged;
   QObject::connect(whichDetailBox,fpDetail,this,&PaintingWidget::setCurrentDetail);
   numOfDetailSlider = new QSlider(Qt::Horizontal);
   numOfDetailSlider->setMinimum(0);
   numOfDetailSlider->setMaximum(64);
   numOfLevelSlider->setValue(8);
   QObject::connect(numOfDetailSlider,&QSlider::valueChanged,this,&PaintingWidget::setNumOfDetail);
   detailAngleSlider = new QSlider(Qt::Horizontal);
   detailAngleSlider->setMinimum(0);
   detailAngleSlider->setMaximum(360);
   QObject::connect(detailAngleSlider,&QSlider::valueChanged,this,&PaintingWidget::setStartOfDetail);
   radiationAnimateBtn = new QPushButton("radiation");
   QObject::connect(radiationAnimateBtn,&QPushButton::clicked,this,&PaintingWidget::radiationCTR);
   loadDetailImageBtn = new QPushButton("Detail Texture");
   QObject::connect(loadDetailImageBtn,&QPushButton::clicked,this,&PaintingWidget::loadDetail);

   levelRotateSlider = new QSlider(Qt::Horizontal);
   levelRotateSlider->setMinimum(0);
   levelRotateSlider->setMaximum(360);
   QObject::connect(levelRotateSlider,&QSlider::valueChanged,this,&PaintingWidget::setSelfRotateOfLevel);
   detailRotateSlider = new QSlider(Qt::Horizontal) ;
   detailRotateSlider->setMinimum(0);
   detailRotateSlider->setMaximum(360);
   QObject::connect(detailRotateSlider,&QSlider::valueChanged,this,&PaintingWidget::setSelfRotateOfDetail);
   setLevelRSlider = new QSlider(Qt::Horizontal);
   setLevelRSlider->setMinimum(250);
   setLevelRSlider->setMinimum(10);
   setLevelRSlider->setValue(50);
   QObject::connect(setLevelRSlider,&QSlider::valueChanged,this,&PaintingWidget::setR);
   detailSizeSlider = new QSlider(Qt::Horizontal);
   detailSizeSlider->setMaximum(100);
   detailSizeSlider->setMinimum(1);
   detailSizeSlider->setValue(50);
   QObject::connect(detailSizeSlider,&QSlider::valueChanged,this,&PaintingWidget::setDetailSize);
   levelSizeSlider = new QSlider(Qt::Horizontal);
   levelSizeSlider = new QSlider(Qt::Horizontal);
   levelSizeSlider->setMinimum(1);
   levelSizeSlider->setMaximum(100);
   levelSizeSlider->setValue(50);
   QObject::connect(levelSizeSlider,&QSlider::valueChanged,this,&PaintingWidget::setLevelSize);
   speedSlider = new QSlider(Qt::Horizontal);
   speedSlider->setMaximum(-10);
   speedSlider->setMinimum(-250);
   speedSlider->setValue(-100);
   QObject::connect(speedSlider, &QSlider::valueChanged,this,&PaintingWidget::setAnimationSpeed);

   render1Btn = new QPushButton("render1");
   QObject::connect(render1Btn,&QPushButton::clicked,this,&PaintingWidget::renderCanvas);
   //render1Btn->show();

   render2Btn = new QPushButton("render2");
   QObject::connect(render2Btn,&QPushButton::clicked,this,&PaintingWidget::renderCanvas2);
   //render2Btn->show();

   blendBtn = new QPushButton("blend");
   QObject::connect(blendBtn, &QPushButton::clicked,this, &PaintingWidget::newBlend);
   //blendBtn->show();

   hueSlider = new QSlider(Qt::Horizontal);
   hueSlider->setMaximum(360);
   hueSlider->setMinimum(0);
   hueSlider->setValue(180);
   saturationSlider = new QSlider(Qt::Horizontal);
   saturationSlider->setMaximum(255);
   saturationSlider->setMinimum(-255);
   saturationSlider->setValue(0);
   valueSlider = new QSlider(Qt::Horizontal);
   valueSlider->setMaximum(255);
   valueSlider->setMinimum(-255);
   valueSlider->setValue(0);
   QObject::connect(hueSlider, &QSlider::valueChanged,this,&PaintingWidget::adjustHsvHue);
   QObject::connect(saturationSlider,&QSlider::valueChanged,this,&PaintingWidget::adjustHsvSaturation);
   QObject::connect(valueSlider,&QSlider::valueChanged,this,&PaintingWidget::adjustHsvValue);
   //hueSlider->show();

   whichLevelLabel = new QLabel("选择主层级");
   numOfLevelLabel = new QLabel("数量");
   levelSelfRotateLabel = new QLabel("自身旋转");
   setLevelRLabel = new QLabel("层级半径");
   levelSizeLabel = new QLabel("大小");
   whichDetailLabel = new QLabel("选择细节层级");
   numOfDetaiLabel = new QLabel("数量");
   detailAngleLabel = new QLabel("位置");
   detailSelfRotateLabel = new QLabel("自身旋转");
   detailSizeLabel = new QLabel("大小");
   speedLabel = new QLabel("动画速度");
   hueLabel = new QLabel("色相");
   saturationLabel = new QLabel("饱和度");
   valueLabel = new QLabel("明度");
   whichLevelLabel->setPalette(palette);
   numOfLevelLabel->setPalette(palette);
   levelSelfRotateLabel->setPalette(palette);
   setLevelRLabel->setPalette(palette);
   levelSizeLabel->setPalette(palette);
   whichDetailLabel->setPalette(palette);
   numOfDetaiLabel->setPalette(palette);
   detailAngleLabel->setPalette(palette);
   detailSelfRotateLabel->setPalette(palette);
   detailSizeLabel->setPalette(palette);
   speedLabel->setPalette(palette);

   //QVBoxLayout* ctrLayout = new QVBoxLayout();
   QGridLayout* ctrLayout = new QGridLayout();
   ctrLayout->addWidget(animationBtn,0,0,1,2);
   ctrLayout->addWidget(whichLevelBox,1,1);
   ctrLayout->addWidget(numOfLevelSlider,2,1);
   ctrLayout->addWidget(levelRotateSlider,3,1);
   ctrLayout->addWidget(setLevelRSlider,4,1);
   ctrLayout->addWidget(levelSizeSlider,5,1);
   ctrLayout->addWidget(loadImageBtn,6,0,1,2);
   ctrLayout->addWidget(whichDetailBox,7,1);
   ctrLayout->addWidget(numOfDetailSlider,8,1);
   ctrLayout->addWidget(detailAngleSlider,9,1);
   ctrLayout->addWidget(detailRotateSlider,10,1);
   ctrLayout->addWidget(detailSizeSlider,11,1);
   ctrLayout->addWidget(loadDetailImageBtn,12,0,1,2);
   ctrLayout->addWidget(radiationAnimateBtn,13,0,1,2);
   ctrLayout->addWidget(speedSlider,14,1);
   ctrLayout->addWidget(hueSlider,15,1);
   ctrLayout->addWidget(saturationSlider,16,1);
   ctrLayout->addWidget(valueSlider,17,1);

   ctrLayout->addWidget(whichLevelLabel,1,0);
   ctrLayout->addWidget(numOfLevelLabel,2,0);
   ctrLayout->addWidget(levelSelfRotateLabel,3,0);
   ctrLayout->addWidget(setLevelRLabel,4,0);
   ctrLayout->addWidget(levelSizeLabel,5,0);
   ctrLayout->addWidget(whichDetailLabel,7,0);
   ctrLayout->addWidget(numOfDetaiLabel,8,0);
   ctrLayout->addWidget(detailAngleLabel,9,0);
   ctrLayout->addWidget(detailSelfRotateLabel,10,0);
   ctrLayout->addWidget(detailSizeLabel,11,0);
   ctrLayout->addWidget(speedLabel,14,0);
   ctrLayout->addWidget(hueLabel,15,0);
   ctrLayout->addWidget(saturationLabel,16,0);
   ctrLayout->addWidget(valueLabel,17,0);

   QGridLayout* cvLayout = new QGridLayout();
   cvLayout->addWidget(render1Btn,0,0);
   cvLayout->addWidget(render2Btn,0,1);
   cvLayout->addWidget(blendBtn,1,0,1,2);
   ctrLayout->addLayout(cvLayout,18,0,2,2);

   QVBoxLayout* empty = new QVBoxLayout();
   QHBoxLayout* mainLayout = new QHBoxLayout();
   mainLayout->addLayout(empty);
   mainLayout->addLayout(ctrLayout);
   mainLayout->setStretchFactor(empty,10);
   mainLayout->setStretchFactor(ctrLayout,3);
   this->setLayout(mainLayout);

   timer = new QTimer(this);
   QObject::connect(timer, &QTimer::timeout,this,&PaintingWidget::updatepainting);
   timer->start(100);

   canvas = QPixmap(1300,700);
   canvas.fill(Qt::black);
}

void PaintingWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    //QPainter painter(&canvas);
    //painter.drawPixmap(50,50,t.level1.width(),t.level1.height(),t.level1);


    float PI = 3.1415;
    QPoint pos;

    for(int i=0;i<5;i++)
    {
       // painter.drawEllipse(t.center,t.r[i],t.r[i]);
        int n = t.numOfLevel[i];
        if(n==0)
            continue;
        QPixmap current = t.level[i];
        if(t.r[i] < 50)
            current = current.scaled(current.width()*(t.r[i]/50.0),current.height()*(t.r[i]/50.0),Qt::KeepAspectRatio);

        float angle = 0.0;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n) * j )/180;
            int posX = t.center.x()  + (t.r[i])*cos(arc);

            pos.setX(posX);
            pos.setY((int)(t.center.y() + (t.r[i])*sin(arc)));

            painter.save();
            painter.translate(pos.x(),pos.y());
            //painter.rotate(-j*(360.0/n)-90);
            //painter.rotate(-90);
            //painter.translate(-pos.x()-current.width()/2,-pos.y()-current.height()/2);
            painter.rotate(j*(360.0/n) + 90 + step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current.width(),current.height(),current);
            painter.restore();

        }

    }

    // boarder image
    {
        int n = t.numOfLevel[t.boarderID];
        QPixmap current = t.level[t.boarderID];       
        int currentR = t.copyR;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n)*j)/180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX,posY);
            painter.rotate(j*(360.0/n) + 90 +step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current);
            painter.restore();
        }

        n = t.numOfDetail[t.boarderID];
        current = t.detail[t.boarderID];
        int begin = t.detail_begin[t.boarderID];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (begin + step + (360.0/n)*j) / 180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX, posY);
            painter.rotate(j*(360.0/n) + 90 + step + begin);
            painter.drawPixmap(-current.width()/2, -current.height()/2,current);
            painter.restore();
        }
    }

    // add detail
    for(int i=0;i<5;i++)
    {
        int n = t.numOfDetail[i];
        QPixmap current = t.detail[i];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (t.detail_begin[i] + step + (360.0/n) * j) / 180;
            int posX = t.center.x() + t.r[i] * cos(arc);
            int posY = t.center.y() + t.r[i] * sin(arc);
            pos.setX(posX);
            pos.setY(posY);
            painter.save();
            painter.translate(pos.x(),pos.y());
            painter.rotate(j*(360.0/n)+90+step+t.detail_begin[i]);
            painter.drawPixmap(-current.width()/2 , -current.height()/2, current);
            painter.restore();
        }
    }

    painter.setPen(QPen(Qt::black,60));
    painter.drawEllipse(t.center,320,320);

    /*
    QPainter renderFinal(this);
    canvas.save("a.png");
    renderFinal.drawPixmap(0,0,canvas);
    */
}

void PaintingWidget::updatepainting()
{
    if(bAnimation){
        step += 1;
        update();
    }
    else
        step = 0;

    if(bRadiation){
        radiusStep = 1;
        setTemplateRadius(radiusStep);
        update();
    }
    else
        radiusStep = 0;

}

void PaintingWidget::animationCtr()
{
    bAnimation = !bAnimation;
    update();
}

void PaintingWidget::radiationCTR()
{
    bRadiation = !bRadiation;
    update();
}

void PaintingWidget::setNumOfLevel(int i)
{
    t.setNumOfLevel(i);
    update();
}
void PaintingWidget::setNumOfDetail(int i)
{
    t.setNumOfDetail(i);
    update();
}

void PaintingWidget::setCurrentLevel(int i)
{
    t.setCurrentLevelCtr(i);
}
void PaintingWidget::setCurrentDetail(int i)
{
    t.setCurrentDetailCtr(i);
}
void PaintingWidget::setStartOfDetail(int degree)
{
    t.setDetailStart(degree);
    update();
}

void PaintingWidget::loadImage()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Image Files((*.png *.jpg)"));
    qDebug() << path;
    QPixmap imageFile;
    imageFile.load(path);
    t.level[t.currentLevel()] = imageFile;
    t.level_origin[t.currentLevel()] = imageFile;
    t.level_origin_hsv[t.currentLevel()] = imageFile;
    //update();
}
void PaintingWidget::loadDetail()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open File"),
                                               ".",
                                               tr("Image Files(*.png *.jpg)"));
    qDebug() << path;
    QPixmap imageFile;
    imageFile.load(path);
    t.detail[t.currentDetail()] = imageFile;
    t.detail_origin[t.currentDetail()] = imageFile;
}

void PaintingWidget::mousePressEvent(QMouseEvent *event)
{
    dragStart = true;
    float distance;
    float dx = event->x() -  t.center.x();
    float dy = event->y() - t.center.y();
    distance = sqrt((dx*dx) + (dy*dy));
    qDebug() << event->x() << event->y();
    qDebug() << distance;
    for(int i=0;i<5;i++)
    {
        if(abs((distance - t.r[i])) < 25){
            startLevel = i;
            qDebug() << startLevel;
        }
    }
    //startLevel = (distance/25 - 1.1)/2;
}
void PaintingWidget::mouseReleaseEvent(QMouseEvent *)
{
    dragStart = false;
    startLevel = -1;
}

void PaintingWidget::mouseMoveEvent(QMouseEvent * event)
{
    bool start = true;
    //int startLevel = -1;
    if(event->buttons()==Qt::LeftButton)
    {
        float distance;
        float dx = event->x() -  t.center.x();
        float dy = event->y() - t.center.y();
        distance = sqrt((dx*dx) + (dy*dy));

        if(startLevel>=0 && startLevel <=4)
        {
            qDebug() << "mouselevel" << startLevel;
            float ratio = (distance-t.r[startLevel])/25;
            qDebug()<<"distance"<<distance;
            qDebug()<<"ratio"<<ratio;
            //t.level[startLevel].scaled(1+ratio,1+ratio);

            if(ratio > 0)
                ratio = 0.1;
            else if(ratio < 0)
                ratio = -0.1;
            else
                ratio = 0;
            t.level[startLevel]=t.level_origin[startLevel].scaled(t.level[startLevel].width()*(1+ratio),t.level[startLevel].height()*(1+ratio),Qt::KeepAspectRatio);
            /*QMatrix rotateM;
            rotateM.rotate(t.selfRotateOfLevel[startLevel]);
            t.level[startLevel] = t.level[startLevel].transformed(rotateM,Qt::SmoothTransformation);
            //t.selfRotate();*/
            update();
        }

    }
}

void PaintingWidget::setTemplateRadius(int step)
{
    t.increaseRaduis(step);
}
void PaintingWidget::setSelfRotateOfLevel(int degree)
{
    t.selfRotateOfLevel[t.currentLevel()] = degree;
    t.selfRotate();
    update();
}
void PaintingWidget::setSelfRotateOfDetail(int degree)
{
    t.selfRotateOfDetail[t.currentDetail()] = degree;
    t.selfRotate();
    update();
}

void PaintingWidget::setR(int r)
{
    t.r[t.currentLevel()] = r;
    update();
}
void PaintingWidget::setDetailSize(int s)
{
    float ratio = s / 50.0;


    qDebug() << ratio;
    t.detail[t.currentDetail()]=t.detail_origin[t.currentDetail()].scaled(t.detail_origin[t.currentDetail()].width()*(ratio),t.detail_origin[t.currentDetail()].height()*(ratio),Qt::KeepAspectRatio);
    QMatrix rotateM;
    rotateM.rotate(t.selfRotateOfDetail[t.currentDetail()]);
    t.detail[t.currentDetail()]=t.detail[t.currentDetail()].transformed(rotateM,Qt::SmoothTransformation);
    update();
}
void PaintingWidget::setLevelSize(int s)
{
    float ratio = s/50.0;
    t.level[t.currentLevel()]=t.level_origin_hsv[t.currentLevel()].scaled(t.level_origin[t.currentLevel()].width()*ratio, t.level_origin[t.currentLevel()].height()*ratio, Qt::KeepAspectRatio);
    QMatrix rotateM;
    rotateM.rotate(t.selfRotateOfLevel[t.currentLevel()]);
    t.level[t.currentLevel()]=t.level[t.currentLevel()].transformed(rotateM,Qt::SmoothTransformation);
    update();
}
void PaintingWidget::setAnimationSpeed(int t)
{
    timer->start(-t);
}

QImage PaintingWidget::Mat2QImage(const Mat &mat)
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
QPixmap PaintingWidget::Mat2QPixmap(const Mat &mat)
{
    QPixmap qpix;
    QImage qimg;
    qimg = Mat2QImage(mat);
    qpix = qpix.fromImage(qimg,Qt::AutoColor);
    return qpix;
}

cv::Mat PaintingWidget::QImage2Mat(QImage image)
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

cv::Mat PaintingWidget::QPixmap2Mat(QPixmap qpix)
{
    QImage qimg;
    qimg = qpix.toImage();

    cv::Mat mat = QImage2Mat(qimg);
    return mat;
}
void PaintingWidget::renderCanvas()
{
    canvas.fill(Qt::black);
    QPainter painter(&canvas);
    float PI = 3.1415;
    QPoint pos;

    for(int i=0;i<5;i++)
    {
       // painter.drawEllipse(t.center,t.r[i],t.r[i]);
        int n = t.numOfLevel[i];
        if(n==0)
            continue;
        QPixmap current = t.level[i];
        if(t.r[i] < 50)
            current = current.scaled(current.width()*(t.r[i]/50.0),current.height()*(t.r[i]/50.0),Qt::KeepAspectRatio);

        float angle = 0.0;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n) * j )/180;
            int posX = t.center.x()  + (t.r[i])*cos(arc);

            pos.setX(posX);
            pos.setY((int)(t.center.y() + (t.r[i])*sin(arc)));

            painter.save();
            painter.translate(pos.x(),pos.y());
            //painter.rotate(-j*(360.0/n)-90);
            //painter.rotate(-90);
            //painter.translate(-pos.x()-current.width()/2,-pos.y()-current.height()/2);
            painter.rotate(j*(360.0/n) + 90 + step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current.width(),current.height(),current);
            painter.restore();

        }

    }

    // boarder image
    {
        int n = t.numOfLevel[t.boarderID];
        QPixmap current = t.level[t.boarderID];
        int currentR = t.copyR;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n)*j)/180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX,posY);
            painter.rotate(j*(360.0/n) + 90 +step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current);
            painter.restore();
        }

        n = t.numOfDetail[t.boarderID];
        current = t.detail[t.boarderID];
        int begin = t.detail_begin[t.boarderID];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (begin + step + (360.0/n)*j) / 180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX, posY);
            painter.rotate(j*(360.0/n) + 90 + step + begin);
            painter.drawPixmap(-current.width()/2, -current.height()/2,current);
            painter.restore();
        }
    }

    // add detail
    for(int i=0;i<5;i++)
    {
        int n = t.numOfDetail[i];
        QPixmap current = t.detail[i];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (t.detail_begin[i] + step + (360.0/n) * j) / 180;
            int posX = t.center.x() + t.r[i] * cos(arc);
            int posY = t.center.y() + t.r[i] * sin(arc);
            pos.setX(posX);
            pos.setY(posY);
            painter.save();
            painter.translate(pos.x(),pos.y());
            painter.rotate(j*(360.0/n)+90+step+t.detail_begin[i]);
            painter.drawPixmap(-current.width()/2 , -current.height()/2, current);
            painter.restore();
        }
    }

    painter.setPen(QPen(Qt::black,60));
    painter.drawEllipse(t.center,320,320);

    canvas.save("render.png");

    QImage qImageRender1;
    qImageRender1.load("./render.png");
    render1 = QImage2Mat(qImageRender1);
    imshow("render1",render1);

}
void PaintingWidget::renderCanvas2()
{
    canvas.fill(Qt::black);
    QPainter painter(&canvas);
    float PI = 3.1415;
    QPoint pos;

    for(int i=0;i<5;i++)
    {
       // painter.drawEllipse(t.center,t.r[i],t.r[i]);
        int n = t.numOfLevel[i];
        if(n==0)
            continue;
        QPixmap current = t.level[i];
        if(t.r[i] < 50)
            current = current.scaled(current.width()*(t.r[i]/50.0),current.height()*(t.r[i]/50.0),Qt::KeepAspectRatio);

        float angle = 0.0;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n) * j )/180;
            int posX = t.center.x()  + (t.r[i])*cos(arc);

            pos.setX(posX);
            pos.setY((int)(t.center.y() + (t.r[i])*sin(arc)));

            painter.save();
            painter.translate(pos.x(),pos.y());
            //painter.rotate(-j*(360.0/n)-90);
            //painter.rotate(-90);
            //painter.translate(-pos.x()-current.width()/2,-pos.y()-current.height()/2);
            painter.rotate(j*(360.0/n) + 90 + step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current.width(),current.height(),current);
            painter.restore();

        }

    }

    // boarder image
    {
        int n = t.numOfLevel[t.boarderID];
        QPixmap current = t.level[t.boarderID];
        int currentR = t.copyR;
        for(int j=0;j<n;j++)
        {
            double arc = PI * (step+(360.0/n)*j)/180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX,posY);
            painter.rotate(j*(360.0/n) + 90 +step);
            painter.drawPixmap(-current.width()/2,-current.height()/2,current);
            painter.restore();
        }

        n = t.numOfDetail[t.boarderID];
        current = t.detail[t.boarderID];
        int begin = t.detail_begin[t.boarderID];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (begin + step + (360.0/n)*j) / 180;
            int posX = t.center.x() + currentR * cos(arc);
            int posY = t.center.y() + currentR * sin(arc);
            painter.save();
            painter.translate(posX, posY);
            painter.rotate(j*(360.0/n) + 90 + step + begin);
            painter.drawPixmap(-current.width()/2, -current.height()/2,current);
            painter.restore();
        }
    }

    // add detail
    for(int i=0;i<5;i++)
    {
        int n = t.numOfDetail[i];
        QPixmap current = t.detail[i];
        for(int j=0;j<n;j++)
        {
            double arc = PI * (t.detail_begin[i] + step + (360.0/n) * j) / 180;
            int posX = t.center.x() + t.r[i] * cos(arc);
            int posY = t.center.y() + t.r[i] * sin(arc);
            pos.setX(posX);
            pos.setY(posY);
            painter.save();
            painter.translate(pos.x(),pos.y());
            painter.rotate(j*(360.0/n)+90+step+t.detail_begin[i]);
            painter.drawPixmap(-current.width()/2 , -current.height()/2, current);
            painter.restore();
        }
    }

    painter.setPen(QPen(Qt::black,60));
    painter.drawEllipse(t.center,320,320);

    canvas.save("render2.png");

    QImage qImageRender2;
    qImageRender2.load("./render2.png");
    render2 = QImage2Mat(qImageRender2);
    imshow("render2",render2);
}

void PaintingWidget::newBlend()
{
    Mat src1 = imread("./render.png");
    Mat src2 = imread("./render2.png");
    hybridWidget = new HybridImage(src1, src2);

    hybridWidget->show();
}

void PaintingWidget::adjustHsvHue(int h)
{
    this->hsv_h = h;
    adjustCurrentHSV();
}
void PaintingWidget::adjustHsvSaturation(int s)
{
    this->hsv_s = s;
    adjustCurrentHSV();
}
void PaintingWidget::adjustHsvValue(int v)
{
    this->hsv_v = v;
    adjustCurrentHSV();
}
QImage PaintingWidget::adjustQImageHSV(QImage input)
{
    Mat src = QImage2Mat(input);
    Mat alpha = src;
    qDebug() << src.type();
    Mat result;
    cv::cvtColor(src,src,CV_BGRA2BGR);
    cv::cvtColor(src,src,CV_BGR2HSV);
    Mat t(src.rows, src.cols, src.type(), Scalar(hsv_h, hsv_s, hsv_v));
    result = src + t;
    cvtColor(result,result,CV_HSV2BGR);
    cvtColor(result,result,CV_BGR2BGRA);
    for(int i=0;i<src.rows;i++)
    {
        for(int j=0;j<src.cols;j++)
        {
            int a = alpha.at<cv::Vec4b>(i,j)[3];
            //qDebug() << "alpha" << a;
            if(a == 0)
            {
                result.at<cv::Vec4b>(i,j)[3] = 0;
            }
        }
    }
    cv::imwrite("imgpng.png",result);
    return Mat2QImage(result);
}
void PaintingWidget::adjustCurrentHSV()
{
    QPixmap currentLevel = t.level_origin[t.currentLevel()];
    QPixmap temp = t.level[t.currentLevel()];

    currentLevel.save("temp.png");
    QImage input;
    input.load("temp.png");
    QImage adjust = adjustQImageHSV(input);
    adjust.save("temp.png");
    currentLevel.load("temp.png");
    t.level_origin_hsv[t.currentLevel()] = currentLevel;

    currentLevel = currentLevel.scaled(temp.width(),temp.height(),Qt::KeepAspectRatio);
    QMatrix rotateM;
    rotateM.rotate(t.selfRotateOfLevel[t.currentLevel()]);
    currentLevel = currentLevel.transformed(rotateM,Qt::SmoothTransformation);
    t.level[t.currentLevel()] = currentLevel;
    update();
}
