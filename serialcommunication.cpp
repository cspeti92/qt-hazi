#include "MainWindowCppSide.h"
#include "SerialCommunication.h"
#include <QQmlProperty>

SerialComm::SerialComm(MainWindowCppSide* MainWindow)
{
    serial = new QSerialPort(this);
    mainWindowFromSerial = MainWindow;
}


void SerialComm::readData()
{
    serialDataBuff = serial->readAll();
    qDebug() << "Uj adat jött: "<<serialDataBuff;
    emit serialDataAvailable(serialDataBuff);
}

void SerialComm::ledRedEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledRedEntryHandler()";
    QByteArray string = "lr\r\n";
    serial->write(string);

}

void SerialComm::ledBlueEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledBlueEntryHandler()";
    QByteArray string = "lb\r\n";
    serial->write(string);

}

void SerialComm::ledGreenEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledGreenEntryHandler()";
    QByteArray string = "lg\r\n";
    serial->write(string);

}

void SerialComm::ledOrangeEntryHandler()
{
    qDebug() << "MainWindowCppSide::ledGreenEntryHandler()";
    QByteArray string = "lo\r\n";
    serial->write(string);

}


void SerialComm::configSavedHandler()
{
    qDebug() << "MainWindowCppSide::configSaved()";

    QString comport_string;
    QVariant comnumberv;
    QVariant baudratev;

    qDebug() << "QML signalok csatlakoztatása";
    QObject::connect(mainWindowFromSerial->discoveryWindowObject, SIGNAL(toggleRed()),
        this, SLOT(ledRedEntryHandler()));
    QObject::connect(mainWindowFromSerial->discoveryWindowObject, SIGNAL(toggleBlue()),
        this, SLOT(ledBlueEntryHandler()));
    QObject::connect(mainWindowFromSerial->discoveryWindowObject, SIGNAL(toggleOrange()),
        this, SLOT(ledOrangeEntryHandler()));
    QObject::connect(mainWindowFromSerial->discoveryWindowObject, SIGNAL(toggleGreen()),
        this, SLOT(ledGreenEntryHandler()));

    /* Serial port signalok csatlakoztatása */
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    baudratev = QQmlProperty::read(mainWindowFromSerial->serialConfigObject, "baudrate");
    comnumberv = QQmlProperty::read(mainWindowFromSerial->serialConfigObject, "comport");

    qDebug() << "baudrate: "<<baudratev.toInt();
    qDebug() << "comnumber: "<<comnumberv.toString();

    comport_string = QString("COM");
    comport_string.append(comnumberv.toString());
    qDebug() << comport_string;

    serial->setPortName(comport_string);
    serial->setBaudRate(baudratev.toInt());
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Soros port inicializálva.";
    }
}

void SerialComm::setMainWindowToSerial(MainWindowCppSide* MainWind)
{
    mainWindowFromSerial = MainWind;
}
