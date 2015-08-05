#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "filemanager.h"
#include "player.h"

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
    void on_actionOpen_File_triggered();
    void on_actionOpen_Dir_triggered();

    void on_actionPrevious_triggered();
    void on_actionNext_triggered();
    void on_actionFirst_triggered();
    void on_actionLast_triggered();

    
signals:
    void reloadFile(QStringList);
    void whichPic(TurnType);

private:
    Ui::MainWindow  *ui;
    FileManager     *pFileManager;
    Player          *pPlayer;
    QStringList     mFileList;
};

#endif // MAINWINDOW_H
