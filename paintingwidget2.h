#ifndef PAINTINGWIDGET2_H
#define PAINTINGWIDGET2_H
#include "template2.h"
#include <QPainter>
#include <QPalette>
#include <QString>
#include <QPaintEvent>
#include <QWidget>
class Paintingwidget2:public QWidget
{
    Q_OBJECT
public:
    Paintingwidget2(QWidget *parent=0);
    int canvasWidth = 1300;
    int canvasHeight = 700;
    Template2 t;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PAINTINGWIDGET2_H
