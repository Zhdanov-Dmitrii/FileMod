#ifndef FILEFILTER_H
#define FILEFILTER_H

#include <QString>

class FileFilter
{
public:
    FileFilter(const QString& mask);

    bool isValid(QString file_path);

private:
    QString mask_;
};

#endif // FILEFILTER_H
