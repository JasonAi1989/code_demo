#include <QtGui>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); 
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

#if 0
    QTranslator translator;
    {
        QStringList environment = QProcess::systemEnvironment();
        QString str;
        bool bFinded = false;

        foreach(str, environment)
        {
            if(str.startsWith("QTDIR="))
            {
                bFinded = true;
                break;
            }
        }

        if(bFinded)
        {
            str = str.mid(6);
            bFinded = translator.load("qt_" + QLocale::system().name(), str.append("/translations/"));
            if(bFinded)
                qApp->installTranslator(&translator);
            else 
                qDebug()<< QObject::tr("没有支持中文的QT国际化翻译软件！");
        }
        else
        {
            qDebug()<< QObject::tr("必须设置QTDIR环境变量！");
            exit(1);
        }
    }
#endif

    MyLogin *pLogin = new MyLogin;
    pLogin->show();

//    MyLogin Login;
//    return Login.exec();
    return app.exec();
}
