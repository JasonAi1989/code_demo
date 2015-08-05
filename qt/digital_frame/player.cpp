#include "player.h"

Player::Player(QWidget *parent)
    :QWidget(parent)
{
    mFileList.clear();
    mCounter = -1;
}

Player::~Player()
{

}

//public slots
void Player::whichPic(TurnType type)
{
    if(mFileList.isEmpty())
    {
        return;
    }

    int size = mFileList.size();

    switch(type)
    {
    case FIRST:
        mCounter = 0;
        break;

    case PREV:
        mCounter--;
        if(mCounter == -1)
        {
            mCounter = size-1;
        }
        break;

    case NEXT:
        mCounter++;
        if(mCounter == size)
        {
            mCounter = 0;
        }
        break;

    case LAST:
        mCounter = size-1;
        break;
    }

    update();
}

//protected:
void Player::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage  image;
    QString file;
    QRect   rect;
    QPixmap background;
    int     width = event->rect().width();
    int     height = event->rect().height();
    int     size = mFileList.size();

    if(mFileList.isEmpty())
    {
        return;
    }

    if(mCounter == -1
        || mCounter == size)
    {
        mCounter = 0;
    }

    file = mFileList.at(mCounter);
    background.fill(Qt::white);

    if(image.load(file))
    {
        //small image
        if(image.width() < width)
        {
            rect.setLeft(event->rect().left() + (width-image.width())/2);
            rect.setWidth(image.width());
        }
        else
        {
            rect.setLeft(event->rect().left());
            rect.setWidth(image.width());
        }

        if(image.height() < height)
        {
            rect.setTop(event->rect().top() + (height-image.height())/2);
            rect.setHeight(image.height());
        }
        else
        {
            rect.setTop(event->rect().top());
            rect.setHeight(image.height());
        }

        //show the background and target image
        painter.drawPixmap(rect, background);
        painter.drawImage(rect, image);
    }
    else
    {
        qDebug()<<"file:"<<file;
        qDebug()<<"bad image.";
    }
}

void Player::mousePressEvent(QMouseEvent *event)
{

}
