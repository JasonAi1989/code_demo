#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pFileManager = new FileManager();
    pPlayer      = new Player();
    mFileList.clear();

    ui->scrollArea->setWidget(pPlayer);

    QObject::connect(this, SIGNAL(reloadFile(QStringList)),
                     pPlayer, SLOT(reload(QStringList)));
    QObject::connect(this, SIGNAL(whichPic(TurnType)),
                     pPlayer, SLOT(whichPic(TurnType)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    mFileList = pFileManager->openPicture();

    if(mFileList.isEmpty())
    {
        return;
    }
    else
    {
        emit reloadFile(mFileList);
    }
}

void MainWindow::on_actionOpen_Dir_triggered()
{
    mFileList = pFileManager->openDirectory();

    if(mFileList.isEmpty())
    {
        return;
    }
    else
    {
        emit reloadFile(mFileList);
    }
}

void MainWindow::on_actionPrevious_triggered()
{
    emit whichPic(PREV);
}

void MainWindow::on_actionNext_triggered()
{
    emit whichPic(NEXT);
}

void MainWindow::on_actionFirst_triggered()
{
    emit whichPic(FIRST);
}

void MainWindow::on_actionLast_triggered()
{
    emit whichPic(LAST);
}
