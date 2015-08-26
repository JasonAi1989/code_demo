#include "mainwindow.h"

CodeLog mylog;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mylog << "test";
    mylog << 20;
    mylog << 3232.345;
}

MainWindow::~MainWindow()
{
    
}
