#include <QQmlContext>
#include "MainWindowCppSide.h"
#include "Logger.h"
#include <QRegularExpression>

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
    QStringList splitStr,splitPart;
    int i;
    // a soros porttól érkező adat átvétele és feldolgozása
    qDebug() << "Adat érkezett a loggerbe"<<data;
    splitStr = data.split(QRegularExpression("\\,"));

    // Megvizsgáljuk, hogy milyen tipusu üzenet érkezett
    // a legelső vessző előtti karakter adja meg
    if(splitStr[0] == "t")
    {
        //egyszerű szöveges üzenet -> kitesszük a szöveges logra
        //*@warning: nem lehet vessző a szöveges részben vessző! /
        logList.append(splitStr[1]);
        mainWindowFromLogger->qmlCont.setContextProperty(QStringLiteral("logModel"),QVariant::fromValue(logList));
    }

    else if(splitStr[0] == "s")
    {
        //státusz üzenet -> fel kell dolgozni
        //ilyenkor a maradék részeket
        if(splitStr.size() != STATUS_RESP_PARTS_NUM)
        {
             qDebug() << "Sérült üzenet vagy meglett változtatva a státusz üzenet!";
        }
        else
        {
            //1-től indulunk, mivel a 0 indexű a parancs típusa
            for(i=1;i < splitStr.size();i++)
            {
                splitPart = splitStr[i].split(QRegularExpression("\\:"));
                //megnézzük, hogy ténylegesen egy kulcs:érték pár jött
                if(splitPart.size() == 2)
                {
                    qDebug() << splitPart[0]<<":"<<splitPart[1];

                }
                else
                {
                   qDebug() << "Sérült üzenet, rossz kulcs:érték pár";
                }

            }
        }

    }

}
