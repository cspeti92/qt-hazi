import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    anchors.fill: parent
    objectName: "DiscoveryWindow"

    // signals for the leds
    signal toggleRed();
    signal toggleOrange();
    signal toggleGreen();
    signal toggleBlue();

    property int margin: 10

    property color selectedColor : "grey"

    // C++ oldal is el tudja érni
    property int lineWidth : 3

    // C++ oldal is el tudja érni
    function selectColor(messageText, color)
    {
        selectedColor = color;
        drawingCanvas.requestPaint();
        eventLogModel.append( { message: messageText, colorCode: color } );
        console.log("selectColor(" + messageText + ", " + color + ")");
    }

    RowLayout {
        id: baseGrid
        anchors.fill: parent
        anchors.margins: margin

        // 1. oszlop

        GroupBox {
            //Layout.fillHeight: true


            ColumnLayout {
                anchors.fill: parent

                Text {
                    text: "Ledek kapcsolása:";
                }

                CheckBox {
                    id: redCheckBox
                    text: "Piros"
                    onClicked: {
                        toggleRed();
                    }
                }

                CheckBox {
                    id: blueCheckBox
                    text: "Kék"
                    onClicked: {
                        toggleBlue();
                    }
                }
                CheckBox {
                    id: orangeCheckBox
                    text: "Narancssárga"
                    onClicked: {
                        toggleOrange();
                    }
                }

                CheckBox {
                    id: greenCheckBox
                    text: "Zöld"
                    onClicked: {
                        toggleGreen();
                    }
                }

            }
        }

        // 2. oszlop

        GroupBox
        {
            Layout.fillHeight: true
            Layout.fillWidth: true


        }

    }
}

