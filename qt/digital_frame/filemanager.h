#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "common.h"

class FileManager : public QObject
{
    Q_OBJECT

public:
    FileManager();

    QStringList openPicture();
    QStringList openDirectory();
    QStringList openTar();

private:
    void setDir(QString dir);
    QString getDir();

signals:
    void hah();

private:
    QStringList mFileList;

};

#endif // FILEMANAGER_H
