#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::instance()->installTranslator(&translator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_E_clicked()
{
    translator.load(":/language/English.qm");
}

void MainWindow::on_pushButton_C_clicked()
{
    translator.load(":/language/Chinese.qm");
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog::getOpenFileName(this, MainWindow::tr("open"), "/", "*.c");
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QMainWindow::changeEvent(e);
}
