#include <QQmlContext>
#include "MainWindowCppSide.h"
#include "Logger.h"

Logger::Logger(MainWindowCppSide* MainWindow)
{
    mainWindowFromLogger = MainWindow;
}

void Logger::setMainWindowToLogger(MainWindowCppSide* MainWindow)
{
    mainWindowFromLogger = MainWindow;
}

void Logger::LoggerProcessMsg(QString data)
{
    // a soros porttól érkező adat átvétele és feldolgozása
    qDebug() << "Adat érkezett a loggerbe"<<data;
    logList.append(data);
    mainWindowFromLogger->qmlCont.setContextProperty(QStringLiteral("logModel"),QVariant::fromValue(logList));
}
