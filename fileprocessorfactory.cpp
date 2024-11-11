#include "fileprocessorfactory.h"
#include "filemodifierprocessor.h"
#include "filewriterprocessor.h"
#include "filewriterwithcounter.h"

std::shared_ptr<IFileProcessor> FileProcessorFactory::create_shared(FileProcessorMode mode, unsigned char xor_byte)
{
    if (mode == FileProcessorMode::WRITE) {
        return std::make_shared<FileWriterProcessor>(xor_byte);
    } else if (mode == FileProcessorMode::MODIFY) {
        return std::make_shared<FileModifierProcessor>(xor_byte);
    } else {
        return std::make_shared<FileWriterWithCounter>(xor_byte);
    }
}
