#include "mainwindow.h"
#include <QApplication>
#include "paintingwidget.h"
#include "paintingwidget2.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "template1ctr.h"
#include <QPushButton>
#include <QSlider>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    PaintingWidget p(&w);
    w.show();

    Paintingwidget2 p2;
    p2.show();

    return a.exec();
}
