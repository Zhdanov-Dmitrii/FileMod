#include "filemanager.h"

#include <QFile>

FileManager::FileManager(std::shared_ptr<IFileProcessor> file_processor, std::shared_ptr<FileFilter> file_filter, bool delete_file)
    : file_processor_(std::move(file_processor))
    , file_filter_(std::move(file_filter))
    , delete_file_(delete_file) {}

void FileManager::run(const QString &input_file_path, const QString &output_file_path)
{
    if (!file_filter_->isValid(input_file_path)) {
        throw std::runtime_error("Файл не подходит по маске");
    }

    file_processor_->process(input_file_path, output_file_path);

    if (delete_file_) {
        QFile input_file;
        if (input_file.exists()) {
            input_file.remove();
        }
    }
}
