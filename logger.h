#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QStringList>
#include "MainWindowCppSide.h"

#define STATUS_RESP_PARTS_NUM 6

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(MainWindowCppSide* MainWindow);
    ~Logger() = default;
    void setMainWindowToLogger(MainWindowCppSide* MainWindow);

signals:

public slots:
    void LoggerProcessMsg(QString data);
private:
    MainWindowCppSide*  mainWindowFromLogger;
    QStringList logList;
};

#endif // LOGGER_H
