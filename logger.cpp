#include <QQmlContext>
#include "MainWindowCppSide.h"
#include "Logger.h"
#include <QRegularExpression>
#include "logdata.h"
#include <memory>
Logger::Logger(MainWindowCppSide* MainWindow):currentState(0.0,0.0,0.0,0.0,false)
{
    mainWindowFromLogger = MainWindow;
}

void Logger::setMainWindowToLogger(MainWindowCppSide* MainWindow)
{
    mainWindowFromLogger = MainWindow;
    mainWindowFromLogger->qmlCont.setContextProperty(QStringLiteral("currentState"),(QObject*)&currentState);
}

void Logger::LoggerProcessMsg(QString data)
{
    QStringList splitStr,splitPart;
    int i;
    float xa,ya,za,ta;
    bool buttona;
    bool statusValueChanged = true;
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
                    if(splitPart[0] == "x")
                    {

                        xa = G_TO_MSS*splitPart[1].toFloat();
                        qDebug() << "xa:"<<xa;
                    }
                    else if(splitPart[0] == "y")
                    {
                        ya = G_TO_MSS*splitPart[1].toFloat();
                    }
                    else if(splitPart[0] == "z")
                    {
                        za = G_TO_MSS*splitPart[1].toFloat();
                    }
                    else if(splitPart[0] == "t")
                    {
                        ta = splitPart[1].toFloat();
                    }
                    else if(splitPart[0] == "b")
                    {
                        buttona = (splitPart[1].toInt() == 0) ? false : true;
                    }
                    else
                    {
                        // nem várt karakter -> megakadályozzuk a fals frissítést
                        statusValueChanged = false;
                    }

                }
                else
                {
                   qDebug() << "Sérült üzenet, rossz kulcs:érték pár";
                }

            }

            if(statusValueChanged == true)
            {
                currentState.updateCurrentLogData(xa,ya,za,ta,buttona);
                mainWindowFromLogger->qmlCont.setContextProperty(QStringLiteral("currentState"),(QObject*)&currentState);
                QVariant returnedValue;
                QVariant xv = xa;
                QVariant yv = ya;
                QVariant zv = za;
                qDebug() << "updateDataset QML függvény meghívása...";
                QMetaObject::invokeMethod(mainWindowFromLogger->discoveryWindowObject, "updateDataset",
                    Q_RETURN_ARG(QVariant, returnedValue),
                    Q_ARG(QVariant, xv),Q_ARG(QVariant, yv),Q_ARG(QVariant, zv));
            }
        }


    }

}
