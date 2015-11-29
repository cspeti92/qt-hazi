import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: "QmlControlKupac"
    width: 640
    height: 480
    visible: true

    // A C++ oldal számára
    objectName: "ApplicationWindow"

    menuBar: MenuBar {
        Menu {
            title: "&Minden"
            MenuItem {
                text: "&ZöldKilép"
                onTriggered: Qt.quit();
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
