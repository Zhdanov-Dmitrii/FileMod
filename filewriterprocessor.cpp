#include "filewriterprocessor.h"
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDebug>

FileWriterProcessor::FileWriterProcessor(unsigned char xor_byte) : xor_byte_(xor_byte) {}

void FileWriterProcessor::process(const QString &path_to_input_file, const QString &path_to_output_dir)
{
    QFile input_file(path_to_input_file);
    if (!input_file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Не удалось открыть входной файл:" + path_to_input_file.toStdString());
    }

    QDir output_dir(path_to_output_dir);
    if (!output_dir.exists() && !output_dir.mkpath(".")) {
        throw std::runtime_error("Не удалось создать директорию:" + path_to_output_dir.toStdString());
    }

    QString output_file_path = output_dir.filePath(QFileInfo(path_to_input_file).fileName());

    QFile output_file(output_file_path);
    if (!output_file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Не удалось открыть выходной файл для записи:" + output_file_path.toStdString());
    }

    write(input_file, output_file);
}

void FileWriterProcessor::write(QFile& input_file, QFile& output_file)
{
    const int bufferSize = 4096;
    QByteArray buffer;
    while (!input_file.atEnd()) {
        buffer = input_file.read(bufferSize);

        for (int i = 0; i < buffer.size(); ++i) {
            buffer[i] = buffer[i] ^ xor_byte_;
        }

        output_file.write(buffer);
    }
}
