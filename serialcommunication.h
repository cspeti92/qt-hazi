#ifndef SERIALCOMMUNICATION
#define SERIALCOMMUNICATION

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "MainWindowCppSide.h"
#include <QTimer>

#define COMM_RECEIVE_MAX_LEN    70

class SerialComm : public QObject
{
    Q_OBJECT

public:
    SerialComm(MainWindowCppSide* MainWindow);
    ~SerialComm() = default;
    void setMainWindowToSerial(MainWindowCppSide* MainWind);
    QString getSerialDataBuff();

private slots:
    void readData();
    void ledRedEntryHandler();
    void ledBlueEntryHandler();
    void ledOrangeEntryHandler();
    void ledGreenEntryHandler();
    void configSavedHandler();
    void sendStatusReq();
    void configResetHandler();
signals:
    void serialDataAvailable(QString data);

private:
    QSerialPort* serial;
    MainWindowCppSide*  mainWindowFromSerial;
    QString serialDataBuff;
    QTimer statusTim;
};


#endif // SERIALCOMMUNICATION

