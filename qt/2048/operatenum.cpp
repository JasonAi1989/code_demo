#include "operatenum.h"
#include <QTime>
#include <QDebug>
#include <QMessageBox>

QString styleSheetTable[13] =
{
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(170, 170, 127);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(0, 231, 231);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(0, 221, 107);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(69, 207, 0);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(241, 241, 120);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(239, 159, 0);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(231, 115, 0);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(186, 92, 139);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(249, 83, 249);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(225, 71, 255);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(170, 170, 127);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(170, 170, 127);}",
    "QLabel{\nmargin:2px;\nborder:2px groove gray;\nborder-radius:10px;\nbackground-color:rgb(170, 170, 127);}"
};

OperateNum::OperateNum(QList<QLabel*> &LabelList)
    :mLabelList(LabelList)
{
    initMetadata();
}

void OperateNum::initMetadata()
{
    memset(mData, 0, SIZE*sizeof(Metadata));

    for(int i=0; i<SIZE; i++)
    {
        mData[i].index = en_null;
        mData[i].styleSheet = &(styleSheetTable[en_null]);
        mData[i].num = 0;
    }
}
void OperateNum::toRight()
{
    for(int i=0; i<LENGTH; i++)
    {
        Metadata tempData[WIDTH];
        memset(tempData, 0, sizeof(Metadata)*WIDTH);

        //move and puls
        for(int j=WIDTH-1, k=WIDTH-1; j>=0 && k>=0; j--)
        {
            if(mData[i*WIDTH + j].index != en_null)
            {
                if(k != WIDTH-1 && tempData[k+1].index == mData[i*WIDTH + j].index)
                {
                    tempData[k+1].index = (Num)((int)tempData[k+1].index + 1);
                    tempData[k+1].num *=2;
                    tempData[k+1].styleSheet = &styleSheetTable[tempData[k+1].index];
                }
                else
                {
                    memcpy(&tempData[k], &mData[i*WIDTH + j], sizeof(Metadata));
                    k--;
                }
            }
        }

        for(int j=0; j<WIDTH; j++)
        {
            mData[i*WIDTH + j].index = tempData[j].index;
            mData[i*WIDTH + j].num = tempData[j].num;
            mData[i*WIDTH + j].styleSheet = &styleSheetTable[mData[i*WIDTH + j].index];
        }
    }
}
void OperateNum::toLeft()
{
    for(int i=0; i<LENGTH; i++)
    {
        Metadata tempData[WIDTH];
        memset(tempData, 0, sizeof(Metadata)*WIDTH);

        //move and puls
        for(int j=0, k=0; j<WIDTH && k<WIDTH; j++)
        {
            if(mData[i*WIDTH + j].index != en_null)
            {
                if(k != 0 && tempData[k-1].index == mData[i*WIDTH + j].index)
                {
                    tempData[k-1].index = (Num)((int)tempData[k-1].index + 1);
                    tempData[k-1].num *=2;
                    tempData[k-1].styleSheet = &styleSheetTable[tempData[k-1].index];
                }
                else
                {
                    memcpy(&tempData[k], &mData[i*WIDTH + j], sizeof(Metadata));
                    k++;
                }
            }
        }

        for(int j=0; j<WIDTH; j++)
        {
            mData[i*WIDTH + j].index = tempData[j].index;
            mData[i*WIDTH + j].num = tempData[j].num;
            mData[i*WIDTH + j].styleSheet = &styleSheetTable[mData[i*WIDTH + j].index];
        }
    }
}
void OperateNum::toUp()
{
    for(int i=0; i<WIDTH; i++)
    {
        Metadata tempData[LENGTH];
        memset(tempData, 0, sizeof(Metadata)*LENGTH);

        //move and puls
        for(int j=0, k=0; j<LENGTH && k<LENGTH; j++)
        {
            if(mData[j*WIDTH + i].index != en_null)
            {
                if(k != 0 && mData[j*WIDTH + i].index == tempData[k-1].index)
                {
                    tempData[k-1].index = (Num)((int)tempData[k-1].index + 1);
                    tempData[k-1].num *=2;
                    tempData[k-1].styleSheet = &styleSheetTable[tempData[k-1].index];
                }
                else
                {
                    memcpy(&tempData[k], &mData[j*WIDTH + i], sizeof(Metadata));
                    k++;
                }
            }
        }

        for(int j=0; j<LENGTH; j++)
        {
            mData[j*WIDTH + i].index = tempData[j].index;
            mData[j*WIDTH + i].num = tempData[j].num;
            mData[j*WIDTH + i].styleSheet = &styleSheetTable[mData[j*WIDTH + i].index];
        }
    }
}
void OperateNum::toDown()
{
    for(int i=0; i<WIDTH; i++)
    {
        Metadata tempData[LENGTH];
        memset(tempData, 0, sizeof(Metadata)*LENGTH);

        //move and puls
        for(int j=LENGTH-1, k=LENGTH-1; j>=0 && k>=0; j--)
        {
            if(mData[j*WIDTH + i].index != en_null)
            {
                if(k != LENGTH-1 && mData[j*WIDTH + i].index == tempData[k+1].index)
                {
                    tempData[k+1].index = (Num)((int)tempData[k+1].index + 1);
                    tempData[k+1].num *=2;
                    tempData[k+1].styleSheet = &styleSheetTable[tempData[k+1].index];
                }
                else
                {
                    memcpy(&tempData[k], &mData[j*WIDTH + i], sizeof(Metadata));
                    k--;
                }
            }
        }

        for(int j=0; j<LENGTH; j++)
        {
            mData[j*WIDTH + i].index = tempData[j].index;
            mData[j*WIDTH + i].num = tempData[j].num;
            mData[j*WIDTH + i].styleSheet = &styleSheetTable[mData[j*WIDTH + i].index];
        }
    }
}

void OperateNum::operateDirection(Direction which)
{
    switch(which)
    {
    case en_toRight:
        toRight();
        break;
    case en_toLeft:
        toLeft();
        break;
    case en_toUp:
        toUp();
        break;
    case en_toDown:
        toDown();
        break;
    default:
        return;
    }
}
void OperateNum::addNum(int amount)
{
    while(amount--)
    {
        QTime ti = QTime::currentTime();
        srand(ti.msec());
        int val = rand();

        int i;
        for(i=0; i<SIZE; i++)
        {
            //要增加数字的位置
            int index = ((val >> i) % SIZE + i) % SIZE;
            if(mData[index].index == en_null)
            {
                Num id = (val % SIZE == 15)?(en_4):(en_2); //只有 1/16的概率出现4
                mData[index].index = id;
                mData[index].num = (id == en_2)?(2):(4);
                mData[index].styleSheet = &(styleSheetTable[id]);

                qDebug()<<"id:"<<id;
                break;
            }
        }

        if(i == SIZE)//满了
        {
            clean();
            addNum(2);

            return;
        }
    }

    updateNum();
}
void OperateNum::updateNum()
{
    for(int i=0; i<SIZE; i++)
    {
        mLabelList.at(i)->setStyleSheet(*(mData[i].styleSheet));

        if(mData[i].index == en_null)
        {
            mLabelList.at(i)->clear();
            continue;
        }
        else
        {
            mLabelList.at(i)->setText(QString::number(mData[i].num));
            QFont font;
            font.setPointSize(20);
            font.setBold(true);
            mLabelList.at(i)->setFont(font);
        }

    }
}
void OperateNum::clean()
{
    initMetadata();
}
