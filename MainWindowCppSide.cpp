#include <QQmlProperty>
#include "MainWindowCppSide.h"
#include <QtSerialPort/QSerialPort>


// További információ és példák a C++ - QML kapcsolatról:
// http://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html

MainWindowCppSide::MainWindowCppSide(QObject *rootObject)
    : QObject(nullptr)
{
    if (!rootObject)
    {
        qDebug() << "Nem találom a rootObject-et.";
    }

    mainWindowObject = findItemByName(rootObject, QString("ApplicationWindow"));
    auto DiscoveryWindow = findItemByName("DiscoveryWindow");
    serial = new QSerialPort(this);

    if (!mainWindowObject)
    {
        qDebug() << "Nem találom a ApplicationWindow objektumot.";
    }

    qDebug() << "QML signalok csatlakoztatása";
    QObject::connect(DiscoveryWindow, SIGNAL(toggleRed()),
        this, SLOT(ledRedEntryHandler()));
    QObject::connect(DiscoveryWindow, SIGNAL(toggleBlue()),
        this, SLOT(ledBlueEntryHandler()));
    QObject::connect(DiscoveryWindow, SIGNAL(toggleOrange()),
        this, SLOT(ledOrangeEntryHandler()));
    QObject::connect(DiscoveryWindow, SIGNAL(toggleGreen()),
        this, SLOT(ledGreenEntryHandler()));

    /* Serial port signalok csatlakoztatása */
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    serial->setPortName(QString("COM3"));
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Soros port inicializálva.";
    }

    qDebug() << "MainWindowCppSide inicializálva.";
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

/* Soros port kezelő függvények  */
void MainWindowCppSide::readData()
{
    QByteArray data = serial->readAll();
    qDebug() << "Uj adat jött: "<<data;
}

void MainWindowCppSide::ledRedEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledRedEntryHandler()";
    QByteArray string = "lr\r\n";
    serial->write(string);

}

void MainWindowCppSide::ledBlueEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledBlueEntryHandler()";
    QByteArray string = "lb\r\n";
    serial->write(string);

}

void MainWindowCppSide::ledGreenEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledGreenEntryHandler()";
    QByteArray string = "lg\r\n";
    serial->write(string);

}

void MainWindowCppSide::ledOrangeEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledGreenEntryHandler()";
    QByteArray string = "lo\r\n";
    serial->write(string);

}