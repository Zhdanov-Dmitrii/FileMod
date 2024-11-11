#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "common.h"
#include "ifileprocessor.h"
#include "filefilter.h"

#include <QString>
#include <QTimer>

class FileManager
{
public:
    FileManager(std::shared_ptr<IFileProcessor> file_processor, std::shared_ptr<FileFilter> file_filter, bool delete_file);

public:
    void run(const QString& input_file_path, const QString& output_file_path);

private:
    std::shared_ptr<IFileProcessor> file_processor_;
    std::shared_ptr<FileFilter> file_filter_;
    bool delete_file_;
};

#endif // FILEMANAGER_H
