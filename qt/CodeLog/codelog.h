/*
This class is used for record the log of the software runtime.
The form of the runtime log is:
[current time] [log info]

The log will be rewritten when start the software, and the append
the log information to the log file.
*/


#ifndef CODELOG_H
#define CODELOG_H

#include <QtGui>
#include <stdio.h>

#define LOG_LENGTH  100

class CodeLog
{
public:
    CodeLog();
    ~CodeLog();

    void recordLog(QString log);
    void recordLog(int log);
    void recordLog(double log);
    void recordLog(char log);
    void recordLog(char* log);

    void operator <<(QString log);
    void operator <<(int log);
    void operator <<(double log);
    void operator <<(char log);
    void operator <<(char* log);

private:
    QString dealInfo(QString info);
    void writeInfo(QString &log);
    void checkLength();

private:
    int     head, tail;
    FILE*   fd;

};

#endif // CODELOG_H
