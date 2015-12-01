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

class MainWindowCppSide : public QObject
{
    Q_OBJECT

public:
    MainWindowCppSide(QObject *rootObject,QQmlContext &qmlContext, SerialComm& sCom, Logger& log);
    ~MainWindowCppSide() = default;
    QQuickItem* mainWindowObject;
    QQuickItem* serialConfigObject;
    QQuickItem* discoveryWindowObject;
    QQmlContext &qmlCont;

public slots:
    /** Esemenykezelo a QML oldali signalokhoz. */
    void configOpenedHandler();

private:
    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
    SerialComm  &mainSerialComm;
    Logger      &mainLogger;
};

#endif // MAINWINDOWCPPSIDE_H
