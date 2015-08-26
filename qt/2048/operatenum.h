#ifndef OPERATENUM_H
#define OPERATENUM_H

#include <QString>
#include <QList>
#include <QLabel>

#define WIDTH   4
#define LENGTH  4
#define SIZE    16

enum Direction
{
    en_toRight,
    en_toLeft,
    en_toUp,
    en_toDown
};

enum Num
{
    en_null = 0,
    en_2,
    en_4,
    en_8,
    en_16,
    en_32,
    en_64,
    en_128,
    en_256,
    en_512,
    en_1024,
    en_2048
};

struct Metadata
{
    Num     index;
    int     num;
    QString *styleSheet;
};

class OperateNum
{
public:
    OperateNum(QList<QLabel*> &LabelList);

    void operateDirection(Direction which);
    void addNum(int amount=1);
    void updateNum();
    void clean();

private:
    void initMetadata();

    void toRight();
    void toLeft();
    void toUp();
    void toDown();

private:
    Metadata        mData[SIZE];
    QList<QLabel*>  mLabelList;
};

#endif // OPERATENUM_H
