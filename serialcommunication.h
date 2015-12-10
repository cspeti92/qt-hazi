#ifndef SERIALCOMMUNICATION
#define SERIALCOMMUNICATION

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "MainWindowCppSide.h"
#include <QTimer>

#define COMM_RECEIVE_MAX_LEN    70
/**
 * @brief A soros kommunikációért felelős osztály. Alapvetően a QSerialPort-t használja.
 * A soros portot beállító ablakon a COM port és a baud rate beállítása után ő nyitja meg
 * a soros portot a beállított értékekkel vagy jelez, ha ez nem sikerült. A soros port lezárását
 * is szintén ő végzi el. A ledeket állító checkboxok szignáljai az ő szlotjaira vannak bekötve,
 * melyek elküldik a megfelelő ledhez tartozó parancsot, hogy a Discovery kit kapcsolja fel vagy le
 * a ledet.A soros kommunikáció sikeres létrejövetele után létrehoz egy timert, mely 500msként küld
 * egy státusz lekérdező parancsot. Erre választként a Discovery elküldi az aktuális állapotát, melyet
 * ez az osztály továbbad a Loggernek feldolgozásra. (a ledeket kapcsolása esetén visszakapott válasznál
 * is ezt teszi)
 */

class SerialComm : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param MainWindow Pointer a főablakra, hogy elérjük ebből az osztályból is
     */
    SerialComm(MainWindowCppSide* MainWindow);
    ~SerialComm() = default;
    /** A Mainwindow később jönn csak létre mint a SerialComm osztály példánya, ezzel
    kötjük össze őket valójában.*/
    void setMainWindowToSerial(MainWindowCppSide* MainWind);

private slots:
    /** Ő olvassa be az adatokat a soros portról. (\n karakterig mely az üzenetek végét jelzi)
        serialDataAvailable szignállal jelez a Loggernek a beérkezett üzenetről */
    void readData();
    /** A piros led checkboxának a klikkelése esetén ő hívódik meg és panracsot küld a led átkapcsolásáért*/
    void ledRedEntryHandler();
    /** A kék led checkboxának a klikkelése esetén ő hívódik meg és panracsot küld a led átkapcsolásáért*/
    void ledBlueEntryHandler();
    /** A narancssárga led checkboxának a klikkelése esetén ő hívódik meg és panracsot küld a led átkapcsolásáért*/
    void ledOrangeEntryHandler();
    /** A zöld led checkboxának a klikkelése esetén ő hívódik meg és panracsot küld a led átkapcsolásáért*/
    void ledGreenEntryHandler();
    /** A start gomb megnyomásakor ő hívódik meg és inicializálja a soros portot */
    void configSavedHandler();
    /** A timer hívja 500msként, hogy kérje le a státuszt */
    void sendStatusReq();
    /** A stop gomb megnyomása estén lezárja a soros portot és kiköti a szignáljait */
    void configResetHandler();
signals:
    /** Ő emittálódik új üzenet megérkezésekor és paraméterként továbbadja azt a Loggernek feldolgozásra */
    void serialDataAvailable(QString data);

private:
    /** Rajta keresztül érjük a soros portot valójában */
    QSerialPort* serial;
    /** A főablakot így éri el a soros kommunikációért felels osztály */
    MainWindowCppSide*  mainWindowFromSerial;
    /** Benne helyezzük el a bejövő üzeneteket */
    QString serialDataBuff;
    /** Timer a periodikus státuszlekérdezéshez */
    QTimer statusTim;
};


#endif // SERIALCOMMUNICATION

