#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QFont>
#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mLabelList.append(ui->label11);
    mLabelList.append(ui->label12);
    mLabelList.append(ui->label13);
    mLabelList.append(ui->label14);
    mLabelList.append(ui->label21);
    mLabelList.append(ui->label22);
    mLabelList.append(ui->label23);
    mLabelList.append(ui->label24);
    mLabelList.append(ui->label31);
    mLabelList.append(ui->label32);
    mLabelList.append(ui->label33);
    mLabelList.append(ui->label34);
    mLabelList.append(ui->label41);
    mLabelList.append(ui->label42);
    mLabelList.append(ui->label43);
    mLabelList.append(ui->label44);

    mOperateNum = new OperateNum(mLabelList);
    mOperateNum->addNum(2);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mOperateNum;
}

void MainWindow::on_pushButtonRight_clicked()
{
    mOperateNum->operateDirection(en_toRight);
    mOperateNum->addNum();
}
void MainWindow::on_pushButtonLeft_clicked()
{
    mOperateNum->operateDirection(en_toLeft);
    mOperateNum->addNum();
}
void MainWindow::on_pushButtonUp_clicked()
{
    mOperateNum->operateDirection(en_toUp);
    mOperateNum->addNum();
}
void MainWindow::on_pushButtonDown_clicked()
{
    mOperateNum->operateDirection(en_toDown);
    mOperateNum->addNum();
}
void MainWindow::on_pushButtonRestart_clicked()
{
    mOperateNum->clean();
    mOperateNum->addNum(2);
}
void MainWindow::on_pushButtonExit_clicked()
{
    close();
}

//void MainWindow::on_actionPanel_triggered(bool checked)
//{
//    if(checked)
//    {
//        ui->line->show();
//        ui->groupBox_2->show();
//        ui->actionPanel->setText("<<");
//    }
//    else
//    {
//        ui->line->hide();
//        ui->groupBox_2->hide();
//        ui->actionPanel->setText(">>");
//    }
//}


