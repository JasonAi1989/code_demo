#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include "operatenum.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void on_pushButtonRight_clicked();
    void on_pushButtonLeft_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();

    void on_pushButtonRestart_clicked();
    void on_pushButtonExit_clicked();

//    void on_actionPanel_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    OperateNum      *mOperateNum;
    QList<QLabel*>  mLabelList;
};

#endif // MAINWINDOW_H
