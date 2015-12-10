#include <QApplication>
#include <QQmlApplicationEngine>
#include "MainWindowCppSide.h"
#include "SerialCommunication.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //grafikonok beregisztrálása
    engine.addImportPath(QStringLiteral("/jbQuick/Charts/"));
    engine.addImportPath(QStringLiteral("D:/egyetem/qt hazi"));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    SerialComm sCom(nullptr);
    Logger log(nullptr);

    MainWindowCppSide mainWindowCppSide(engine.rootObjects()[0],*engine.rootContext(),sCom,log);
    Q_UNUSED(mainWindowCppSide);

    return app.exec();
}

