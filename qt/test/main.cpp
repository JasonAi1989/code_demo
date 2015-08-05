#include <QtGui>
#include "test.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MyTest test;
    test.show();

    return app.exec();
}
