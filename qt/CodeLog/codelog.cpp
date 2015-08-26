#include "codelog.h"

CodeLog::CodeLog()
{
    fd = fopen("log.txt", "w");
    head = tail = 0;
}

CodeLog::~CodeLog()
{
    fclose(fd);
}

void CodeLog::recordLog(QString log)
{
    tail++;

    writeInfo(dealInfo(log));
}

void CodeLog::recordLog(int log)
{
    tail++;

    writeInfo(dealInfo(QString::number(log)));
}

void CodeLog::recordLog(double log)
{
    tail++;

    writeInfo(dealInfo(QString::number(log)));
}

void CodeLog::recordLog(char log)
{
    tail++;

    QString tmpLog = log;
    writeInfo(dealInfo(tmpLog));
}

void CodeLog::recordLog(char* log)
{
    tail++;

    QString tmpLog = log;
    writeInfo(dealInfo(tmpLog));
}

void CodeLog::operator <<(QString log)
{
    tail++;

    writeInfo(dealInfo(log));
}

void CodeLog::operator <<(int log)
{
    tail++;

    writeInfo(dealInfo(QString::number(log)));
}

void CodeLog::operator <<(double log)
{
    tail++;

    writeInfo(dealInfo(QString::number(log)));
}

void CodeLog::operator <<(char log)
{
    tail++;

    QString tmpLog = log;
    writeInfo(dealInfo(tmpLog));
}

void CodeLog::operator <<(char* log)
{
    tail++;

    QString tmpLog = log;
    writeInfo(dealInfo(tmpLog));
}

QString CodeLog::dealInfo(QString info)
{
    QString time = QTime::currentTime().toString("hh:mm:ss");
    QString realLog = "[" + QString::number(tail) + "] [" + time + "] [" + info + "]\n";

    return realLog;
}

void CodeLog::writeInfo(QString &log)
{
//    checkLength();

    QByteArray logArray = log.toUtf8();
    fwrite(logArray.data(), logArray.size(), 1, fd);
    fflush(fd);
}

void CodeLog::checkLength()
{
}
