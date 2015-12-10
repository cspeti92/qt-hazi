#include <QQmlProperty>
#include "MainWindowCppSide.h"
#include <QtSerialPort/QSerialPort>
#include <QQmlContext>
#include <QQuickView>
#include <QStringList>
#include "SerialCommunication.h"
#include "Logger.h"

MainWindowCppSide::MainWindowCppSide(QObject *rootObject,QQmlContext &qmlContext, SerialComm& sCom, Logger& log)
    : QObject(nullptr),qmlCont(qmlContext), mainSerialComm(sCom),mainLogger(log)
{
    if (!rootObject)
    {
        qDebug() << "Nem találom a rootObject-et.";
    }

    mainWindowObject = findItemByName(rootObject, QString("ApplicationWindow"));

    if (!mainWindowObject)
    {
        qDebug() << "Nem találom a ApplicationWindow objektumot.";
    }
    else
    {
        qDebug() << "MainWindowCppSide inicializálva.";
        discoveryWindowObject = findItemByName("DiscoveryWindow");
        if (!discoveryWindowObject)
        {
            qDebug() << "Nem találom a DiscoveryWindow objektumot.";
        }
        else
        {
             qDebug() << "UI inicializálása kész!";
             // soros port konfig szignál bekötése
             connect(mainWindowObject,SIGNAL(configOpened()),this,SLOT(configOpenedHandler()));
             //beállítjuk a main loggerét és serial commját, hogy később elérjük ezeket
             mainSerialComm.setMainWindowToSerial(this);
             mainLogger.setMainWindowToLogger(this);
             //összekötjük őket egyből, hogy ne a SerialCommunicationből kelljen
             connect(&mainSerialComm,&SerialComm::serialDataAvailable,&mainLogger,&Logger::LoggerProcessMsg);
        }
    }
}

QQuickItem* MainWindowCppSide::findItemByName(const QString& name)
{
    Q_ASSERT(mainWindowObject != nullptr);
    if (mainWindowObject->objectName() == name)
    {
        return mainWindowObject;
    }
    return findItemByName(mainWindowObject->children(), name);
}

QQuickItem* MainWindowCppSide::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

QQuickItem* MainWindowCppSide::findItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = findItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}


void MainWindowCppSide::configOpenedHandler()
{
    qDebug() << "Config opened!";
    serialConfigObject = findItemByName("SerialConfigWindow");
    if (!serialConfigObject)
    {
        qDebug() << "Nem találom a SerialConfig objektumot.";
    }
    else
    {
        //megnyitották a konfig ablakot -> bekötjük a szignáljait a SerialComm osztály slotjaira
        connect(serialConfigObject,SIGNAL(serialConfigDone()),&mainSerialComm,SLOT(configSavedHandler()));
        connect(serialConfigObject,SIGNAL(stopSimulation()),&mainSerialComm,SLOT(configResetHandler()));
        //beállítjuk a logdata törlésre szolgáló slotot is
        connect(serialConfigObject,SIGNAL(resetLogData()),&mainLogger, SLOT(resetLogger()));
    }

}


