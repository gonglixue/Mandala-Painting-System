#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    resize(1300,600);
    setWindowTitle(tr("Main Window"));

}

MainWindow::~MainWindow()
{

}


