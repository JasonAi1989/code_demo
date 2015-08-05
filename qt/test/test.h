#ifndef _TEST_H_
#define _TEST_H_

#include <QtGui>
#include "ui_test.h"

class MyTest :public QWidget, public Ui_Form
{
public:
    MyTest(QWidget* parent=0);
};

#endif
