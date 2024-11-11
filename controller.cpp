#include "controller.h"
#include "fileprocessorfactory.h"

#include <QMessageBox>

Controller::Controller(QObject *parent) : QObject(parent), timer_(new QTimer(this)) {}

void Controller::run(const QString& input, const QString& output, const QString& mask,
         bool delete_file, const QString& processor_mode, const QString& start_mode,
         int interval, unsigned char xor_byte)
{
    stopTimer();

    FileProcessorMode mode = strToFileProcessorMode(processor_mode);

    auto processor = FileProcessorFactory::create_shared(mode, xor_byte);
    auto filter = std::make_shared<FileFilter>(mask);

    manager_ = std::make_shared<FileManager>(std::move(processor), std::move(filter), delete_file);

    if (start_mode == "Один запуск")
        run(input, output);
    else
        runTimer(input, output, interval);
}

void Controller::run(const QString &input, const QString &output)
{
    try {
        manager_->run(input, output);
    } catch (std::runtime_error& err) {
        QMessageBox::critical(nullptr, "Ошибка", QString(err.what()));
    }
}

void Controller::runTimer(const QString &input, const QString &output, int interval)
{
    timer_->setInterval(interval * 1000);
    connect(timer_, &QTimer::timeout, this, [this, input, output](){ run(input, output); });

    timer_->start(interval * 1000);
}

void Controller::stopTimer()
{
    timer_->disconnect();
    timer_->stop();
}

FileProcessorMode Controller::strToFileProcessorMode(const QString &str)
{
    if(str == "Перезаписать")
        return FileProcessorMode::WRITE;
    else if (str == "Модифицировать")
        return FileProcessorMode::MODIFY;
    else
        return FileProcessorMode::COUNTER;
}
