#ifndef FILEWRITERPROCESSOR_H
#define FILEWRITERPROCESSOR_H

#include "ifileprocessor.h"
#include <QFile>

class FileWriterProcessor : public IFileProcessor
{
    unsigned char xor_byte_;
public:
    FileWriterProcessor(unsigned char xor_byte);

    void process(const QString &path_to_input_file, const QString &path_to_output_dir) override;

protected:
    void write(std::unique_ptr<QFile> input_file, std::unique_ptr<QFile> output_file);
};

#endif // FILEWRITERPROCESSOR_H
