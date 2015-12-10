#pragma once
#ifndef MAINWINDOWCPPSIDE_H
#define MAINWINDOWCPPSIDE_H
#include <QObject>
#include <QQuickItem>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QQmlContext>


class Logger;
class SerialComm;
/**
 * @brief A főablak kezeléséért felelős osztály.
 * Megkeresi a QML oldalon létrehozott itemeket és eltárolja azokat, hogy később elérjük őket.
 * Beköti a soros port kezelő ablak megfelelő szignáljait a soros port kezelő osztály szlotjaira.
 * Ezen kívül ő köti be a soros kommunikációért felelős osztály szignálját a Logger feloldozó
 * szlotjára.
 */
class MainWindowCppSide : public QObject
{
    Q_OBJECT

public:
    /**
     * Konstruktor a főablakot kezelő osztályhoz.
     * @param rootObject Rajta keresztül érjük el az alkalmazás QML részét.
     * @param qmlContext Rajta keresztül érjük a QML oldali változókat, fügvényeket
     * @param sCom Referencia a soros portot kezelő osztály egy példányára.
     * @param log Referencia a Logger osztály egy példányára.
     */
    MainWindowCppSide(QObject *rootObject,QQmlContext &qmlContext, SerialComm& sCom, Logger& log);
    ~MainWindowCppSide() = default;
    /** Mutató a főablak itemjére */
    QQuickItem* mainWindowObject;
    /** Mutató a soros konfig ablak itemjére */
    QQuickItem* serialConfigObject;
    /** Mutató a Discovery ablak itemjére */
    QQuickItem* discoveryWindowObject;
    /** Refrencia melyen keresztül elérjük a QML oldali függvényeket és változókat */
    QQmlContext &qmlCont;

public slots:
    /** Esemenykezelo a QML oldali signalokhoz */
    void configOpenedHandler();

private:
    /** Megkeres egy itemet név alapján */
    QQuickItem* findItemByName(const QString& name);
    /** Megkeres egy itemet név és rootObject alapján */
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    /** Megkeres egy itemet név és egy lista alapján */
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
    /** Ezen keresztül éri a soros portot kezelő osztály példányát a főablak */
    SerialComm  &mainSerialComm;
    /** Ezen keresztül éri a logokat kezelő osztály példányát a főablak */
    Logger      &mainLogger;
};

#endif // MAINWINDOWCPPSIDE_H
