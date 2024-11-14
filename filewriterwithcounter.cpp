#include "filewriterwithcounter.h"

#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDebug>

FileWriterWithCounter::FileWriterWithCounter(unsigned char xor_byte) : FileWriterProcessor(xor_byte) {}

void FileWriterWithCounter::process(const QString &path_to_input_file, const QString &path_to_output_dir)
{
    auto input_file = std::make_unique<QFile>(path_to_input_file);
    if (!input_file->open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Не удалось открыть входной файл:" + path_to_input_file.toStdString());
    }

    QDir output_dir(path_to_output_dir);
    if (!output_dir.exists() && !output_dir.mkpath(".")) {
         throw std::runtime_error("Не удалось создать директорию:" + path_to_output_dir.toStdString());
    }
    QFileInfo input_file_info(path_to_input_file);
    QString output_file_path = output_dir.filePath(input_file_info.fileName());

    auto output_file = std::make_unique<QFile>(output_file_path);
    int counter = 1;
    while(!output_file->exists()){
        QString new_file_name = input_file_info.baseName() + "(" +  QString::number(counter++) + ")" + input_file_info.suffix();
        output_file_path = output_dir.filePath(new_file_name);
        output_file = std::make_unique<QFile>(output_file_path);
    }

    if (!output_file->open(QIODevice::WriteOnly)) {
         throw std::runtime_error("Не удалось открыть выходной файл для записи:" + output_file_path.toStdString());
    }

    write(std::move(input_file), std::move(output_file));
}
