#ifndef FILEPROCESSORFACTORY_H
#define FILEPROCESSORFACTORY_H

#include "common.h"
#include "ifileprocessor.h"

class FileProcessorFactory
{
public:
    static std::shared_ptr<IFileProcessor> create_shared(FileProcessorMode mode, unsigned char xor_byte);
};

#endif // FILEPROCESSORFACTORY_H
