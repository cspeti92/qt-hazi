#pragma once
#ifndef MAINWINDOWCPPSIDE_H
#define MAINWINDOWCPPSIDE_H
#include <QObject>
#include <QQuickItem>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>

class MainWindowCppSide : public QObject
{
    Q_OBJECT

public:
    MainWindowCppSide(QObject *rootObject);
    ~MainWindowCppSide() = default;

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

};

#endif // MAINWINDOWCPPSIDE_H
