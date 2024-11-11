#ifndef IFILEPROCESSOR_H
#define IFILEPROCESSOR_H

#include <QString>

class IFileProcessor {
public:
    virtual void process(const QString& path_to_input_file, const QString& path_to_output_dir) = 0 ;
};

#endif // IFILEPROCESSOR_H
