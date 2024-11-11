#ifndef FILEWRITERWITHCOUNTER_H
#define FILEWRITERWITHCOUNTER_H

#include "filewriterprocessor.h"

class FileWriterWithCounter : public FileWriterProcessor
{
public:
    FileWriterWithCounter(unsigned char xor_byte);

    void process(const QString &path_to_input_file, const QString &path_to_output_dir) override;
};

#endif // FILEWRITERWITHCOUNTER_H
