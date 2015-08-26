#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

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
    void on_pushButton_E_clicked();
    void on_pushButton_C_clicked();
    void on_pushButton_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTranslator translator;
};

#endif // MAINWINDOW_H
