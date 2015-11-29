import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "globalvars.js" as Global

ApplicationWindow {
    title: "DiscoverySimulator"
    width: 640
    height: 480
    visible: true
    id: root
    property variant win;  // you can hold this as a reference..

    // A C++ oldal számára
    objectName: "ApplicationWindow"

    signal configOpened();

    menuBar: MenuBar {
        Menu {
            title: "&Minden"
            MenuItem {
                text: "&Soros Port beállítása"
                onTriggered:
                {
                    if(Global.ConfigOpened == false)
                    {
                        Global.ConfigOpened = true;
                        var component = Qt.createComponent("SerialPortConfig.qml");
                        win = component.createObject(root);
                        win.show();
                        configOpened();
                    }
                }
            }
            MenuItem {
                text: "&Kilépés"
                onTriggered: Qt.quit();
            }
        }
    }

    DiscoveryWindow {
    }

}
