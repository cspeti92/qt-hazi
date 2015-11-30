#pragma once
#ifndef MAINWINDOWCPPSIDE_H
#define MAINWINDOWCPPSIDE_H
#include <QObject>
#include <QQuickItem>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QQmlContext>
#include <QStringList>

class MainWindowCppSide : public QObject
{
    Q_OBJECT

public:
    MainWindowCppSide(QObject *rootObject, QQmlContext &qmlContext);
    ~MainWindowCppSide() = default;

    QStringList logList;

public slots:
    /** Eseménykezelő a QML oldali addGreenEntry signalhoz. */
    void ledRedEntryHandler();
    void ledBlueEntryHandler();
    void ledOrangeEntryHandler();
    void ledGreenEntryHandler();

private slots:
    //void writeData(const QByteArray &data);
    void readData();

private:
    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
    QQuickItem* mainWindowObject;
    QSerialPort *serial;
    QQmlContext &qmlCont;


};

#endif // MAINWINDOWCPPSIDE_H
