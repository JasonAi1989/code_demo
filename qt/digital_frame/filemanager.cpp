#include "filemanager.h"

//public
FileManager::FileManager()
{
    mFileList.clear();
}

QStringList FileManager::openPicture()
{
    QString     fullFile;

    fullFile = QFileDialog::getOpenFileName(0, tr("Open file"),
                        getDir(),tr("Images (*.png *.jpg)"));

    mFileList.clear();

    if(fullFile.isNull())
    {
        return mFileList;
    }

    mFileList.append(fullFile);

    QFileInfo   fi(fullFile);
    setDir(fi.absoluteFilePath());

    return mFileList;
}

QStringList FileManager::openDirectory()
{
    QString     fullDir;

    fullDir = QFileDialog::getExistingDirectory(0, tr("Open directory"), getDir());

    mFileList.clear();

    if(fullDir.isNull())
    {
        return mFileList;
    }

    QDir realDir(fullDir);
    QStringList filter;
    QStringList tmpFileList;
    int         size;
    int         i;

    filter << "*.jpg" << "*.png" << "*.jpeg"
           << "*.bmp" << "*.gif" << "*.pbm"
           << "*.pgm" << "*.ppm" << "*.tiff"
           << "*.xbm" << "*.xpm" << "*.JPG";

    tmpFileList = realDir.entryList(filter, QDir::Files);
    size = tmpFileList.size();

    for(i=0; i<size; i++)
    {
        mFileList.append(fullDir + "/" + tmpFileList.at(i));
    }

    setDir(fullDir);

    qDebug()<<"mFileList size:"<<mFileList.size();
    return mFileList;
}

QStringList FileManager::openTar()
{

}

//private
void FileManager::setDir(QString dir)
{
    QSettings   settings(COMPANY, APP);
    settings.setValue(KEY, dir);
}

QString FileManager::getDir()
{
    QSettings   settings(COMPANY, APP);
    return settings.value(KEY).toString();
}
