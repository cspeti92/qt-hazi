#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QStringList>
#include "MainWindowCppSide.h"
#include "logdata.h"
#define STATUS_RESP_PARTS_NUM 6
#define G_TO_MSS              9.81
/**
 * @brief A Logger összeköttetésben áll a soros kommunikációért felelős SerialComm
 * osztállyal. A SerialComm jelzi mindig a Loggernek, hogy beérkezett egy új üzenet.
 * A SerialComm serialDataAvailable szignálja kapcsolódik a Logger LoggerProcessMsg
 * szlotjára. Így gyakorlatilag a soros kommunikációért felelős osztály továbbít egy
 * nyer üzenetet a Loggernek, mely ezt felparszolja és megjeleníti a képernyőn.
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    /**
     * A konstruktor
     * @param MainWindow Mutató a főablak kezelő osztály egy példányára.
     * Ezen keresztül érjük el a főablakot, hogy adatokat tudjunk megjeleníteni.
     */
    Logger(MainWindowCppSide* MainWindow);
    ~Logger() = default;
    void setMainWindowToLogger(MainWindowCppSide* MainWindow);

signals:
public slots:
    /**
     * Ez a függvény felelős a paraméterként kapott - soros portról érkező -
     * adat felparszolásáért és a képernyőn való megjelenítéséért.
     * @param data A soros portról érkező adat.
     */
    void LoggerProcessMsg(QString data);
    /** QMLből a stop gomb megnyomásakor erre a szlotra csatlakozva jelzünk, hogy
     * az aktuális állapotot reszeteljük és ezt a reszetelt állapotot jelenítsük meg*/
    void resetLogger();
private:
    /** A logger ezen keresztül éri el a főablakot, hogy rajzolni tudjon rá */
    MainWindowCppSide*  mainWindowFromLogger;
    /** A szöveges logok ebbe a listába kerülnek be, majd ezek kerülnek megjelenítésre */
    QStringList logList;
    /** Az aktuális állapotot ebben tároljuk */
    LogData currentState;

};

#endif // LOGGER_H
