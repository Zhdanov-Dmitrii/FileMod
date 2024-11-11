#include "filemodifierprocessor.h"

#include <QIODevice>
#include <QFile>
#include <QDebug>
#include <QDir>


FileModifierProcessor::FileModifierProcessor(unsigned char xor_byte) : xor_byte_(xor_byte) {}

void FileModifierProcessor::process(const QString &path_to_input_file, const QString &path_to_output_dir)
{
    QFile inputFile(path_to_input_file);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Не удалось открыть входной файл:" + path_to_input_file.toStdString());
    }

    QDir outputDir(path_to_output_dir);
    if (!outputDir.exists() && !outputDir.mkpath(".")) {
        throw std::runtime_error("Не удалось создать директорию:" + path_to_output_dir.toStdString());
    }

    QString output_file_path = outputDir.filePath(QFileInfo(path_to_input_file).fileName());

    QFile outputFile(output_file_path);
    if (!outputFile.open(QIODevice::ReadWrite)) {
        throw std::runtime_error("Не удалось открыть выходной файл для записи:" + output_file_path.toStdString());
    }

    outputFile.seek(0);

    const int bufferSize = 4096; // Размер буфера
    QByteArray buffer;
    char byte;

    while (!inputFile.atEnd()) {
        buffer = inputFile.read(bufferSize);

        for (int i = 0; i < buffer.size(); ++i) {
            byte = buffer[i];
            buffer[i] = byte ^ xor_byte_; // Применяем XOR
        }

        // Записываем изменённый буфер в выходной файл
        outputFile.write(buffer);
    }
}
