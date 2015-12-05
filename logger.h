#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QStringList>
#include "MainWindowCppSide.h"
#include "logdata.h"
#define STATUS_RESP_PARTS_NUM 6
#define G_TO_MSS              9.81

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(MainWindowCppSide* MainWindow);
    ~Logger() = default;
    void setMainWindowToLogger(MainWindowCppSide* MainWindow);
    int cntr;

signals:
public slots:
    void LoggerProcessMsg(QString data);
private:
    MainWindowCppSide*  mainWindowFromLogger;
    QStringList logList;
    QList<QObject*> dataList;
    LogData currentState;

};

#endif // LOGGER_H
