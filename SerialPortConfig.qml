import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import "globalvars.js" as Global



Window {
    title: "Beállítás"

    width: 200
    height: 200
    minimumHeight: 200
    minimumWidth: 200
    maximumHeight: 200
    maximumWidth: 200

    onClosing:
    {
      console.log("Configure Serial Port Closed");
      Global.ConfigOpened = false;
    }

    Item
    {
        objectName: "SerialConfigWindow"
        property string comport
        property int baudrate
        comport: "-1"
        baudrate: 9600
        signal serialConfigDone();
        id: serialId

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }

        GroupBox
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            anchors.fill: parent
            ColumnLayout
            {
                anchors.fill: parent

                GroupBox
                {
                    title: "COM port beállítása:";

                    ColumnLayout
                    {
                        TextField
                        {
                            id: textField1
                            validator: IntValidator {bottom:0 ; top: 255;}
                            placeholderText: qsTr("COMx")
                            onAccepted:
                            {
                                console.debug(text)
                                console.log("Com port accepted");
                                serialId.comport = text;
                            }

                        }

                        Text
                        {
                            text: "Nyomj entert a véglegesítéshez!";
                        }
                    }

                }

                GroupBox
				{
                    Layout.fillWidth: true
                    title: "Baudrate:";

                    ComboBox
                    {
                        id: comboBox1
                        currentIndex: 0
                            model: ListModel
                            {
                                id: cbItems
                                ListElement { rate: 9600; }
                                ListElement { rate: 19200; }
                                ListElement { rate: 38400; }
                                ListElement { rate: 57600; }
                                ListElement { rate: 115200; }
                            }
                            Layout.fillWidth: true
                            onCurrentIndexChanged:
                            {
                                console.debug(cbItems.get(currentIndex).rate)
                                serialId.baudrate = cbItems.get(currentIndex).rate;
                            }

                    }
				}
	

				Button
				{
					id: validateSerialConfig
					Layout.fillWidth: true
					text: "Mentés!"
					onClicked:
					{
                        if(serialId.comport != "-1")
						{
							console.log("Serial configuration finished");
                            /* TODO: Handle the real status of the serial port */
                            serialId.serialConfigDone();
						}
						else
						{
                            messageDialog.warn(qsTr("Válassz ki egy COM portot!"));
						}
					}
				}

			}
		}

		MessageDialog 
		{
			id: messageDialog
            title: qsTr("Figyelmeztetés")
            function warn(caption) {
                messageDialog.text = caption;
                messageDialog.open();
            }

		}
	}

}
