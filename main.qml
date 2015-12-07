import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "globalvars.js" as Global




ApplicationWindow {
    title: "DiscoverySimulator"
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    id: root
    property variant win;
    property bool serialWinFirstOpen : true; //elég csak 1 példány az ablakból

    // A C++ oldal számára
    objectName: "ApplicationWindow"

    signal configOpened();

    menuBar: MenuBar {
        Menu {
            title: "&Beállítások"
            MenuItem {
                text: "&Soros Port beállítása"
                onTriggered:
                {
                    if(Global.ConfigOpened == false)
                    {
                        Global.ConfigOpened = true;
                        if(serialWinFirstOpen == true)
                        {
                            var component = Qt.createComponent("SerialPortConfig.qml");
                            win = component.createObject(root);
                            serialWinFirstOpen = false;
                        }
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
