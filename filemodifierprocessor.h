#ifndef FILEMODIFIERPROCESSOR_H
#define FILEMODIFIERPROCESSOR_H

#include "ifileprocessor.h"

class FileModifierProcessor : public IFileProcessor
{
    unsigned char xor_byte_;
public:
    FileModifierProcessor(unsigned char xor_byte);

    void process(const QString &path_to_input_file, const QString &path_to_output_dir) override;
};

#endif // FILEMODIFIERPROCESSOR_H
