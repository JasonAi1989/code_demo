1.About use the Designer to make the project
First, build the new desinger, and layout in it, then save!
Second, qmake -project -o file.pro, qmake, make(you will be failure), 
then, you will find there is ui_XXX.h file 
Third, build the XXX.h and XXX.cpp to creat the object, in the XXX.h 
file ,you can write in this way:
    include "ui_XXX.h"

    class MyTest :: public QWidget, public Ui_Form
    {
    public:
        MyTest(QWidget* parent=0);
    };

In XXX.cpp file, you can write in this way:
    include "test.h"

    MyTest::MyTest(QWidget* parent=0)
    :QWidget(parent)
    {
        setupUi(this);  //this is init the form in this object
    }

In main.cpp file, you can write in this way:
    include "test.h"

    int main(int argc,char** argv)
    {
        QApplication app(argc, argv);

        MyTest test;
        test.show();

        return app.exec();
    }
Finally, the mini system is ok, you can try it by yourself!!    
