#include "filefilter.h"

#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

FileFilter::FileFilter(const QString &mask) : mask_(mask) {}

bool FileFilter::isValid(QString file_path)
{
    QRegularExpression regex(mask_);
    QFile file(file_path);
    return file.exists() && regex.match(QFileInfo(file).fileName()).hasMatch();
}
