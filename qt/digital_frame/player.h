#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

class Player : public QWidget
{
    Q_OBJECT
    
public:
    explicit Player(QWidget *parent = 0);
    ~Player();
    
public slots:
    void reload(QStringList fileList){mFileList = fileList;update();}
    void whichPic(TurnType type);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QStringList     mFileList;
    volatile int    mCounter;
};

#endif // PLAYER_H
