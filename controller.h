#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "common.h"
#include "filemanager.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

public slots:
    void run(const QString& input, const QString& output, const QString& mask,
             bool delete_file, const QString& processor_mode, const QString& start_mode,
             int interval, unsigned char xor_byte);
    void stopTimer();

private:
    FileProcessorMode strToFileProcessorMode(const QString& str);
    void run(const QString& input, const QString& output);

    void runTimer(const QString& input, const QString& output, int interval);



private:
    std::shared_ptr<FileManager> manager_;
    QTimer* timer_;
};

#endif // CONTROLLER_H
