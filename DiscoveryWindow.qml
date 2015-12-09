import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import jbQuick.Charts 1.0
import "."
import "QChart.js" as Charts
import "ChartData.js" as ChartsData

Item {
    anchors.fill: parent
    objectName: "DiscoveryWindow"
    id:discId

    // signals for the leds
    signal toggleRed();
    signal toggleOrange();
    signal toggleGreen();
    signal toggleBlue();

    property int margin: 10
    property   var chartOptions: ({})
    property double rawdata: 4.0
    property int factor:5
    //az első oszlop szélessé fix 25
    property int axisTitleWidth: 90
    property int firstColWidth:160
    property int graphsWidth:((root.width-firstColWidth-axisTitleWidth)/2)
    property int graphsHeight: root.height/3
    property double factorx: root.width/root.minimumWidth
    property double factory: root.height/root.minimumHeight

    function updateDataset(newx,newy,newz)
    {
        ChartsData.ChartLineDataX.labels.push("");
        ChartsData.ChartLineDataX.datasets[0].data.push(newx);
        chart_linex.chartOptions = false;
        chart_linex.repaint();

        ChartsData.ChartLineDataY.labels.push("");
        ChartsData.ChartLineDataY.datasets[0].data.push(newy);
        chart_liney.chartOptions = false;
        chart_liney.repaint();

        ChartsData.ChartLineDataZ.labels.push("");
        ChartsData.ChartLineDataZ.datasets[0].data.push(newz);
        chart_linez.chartOptions = false;
        chart_linez.repaint();

    }

    function resetGraphs()
    {
        ChartsData.ChartLineDataX.labels.splice(1,ChartsData.ChartLineDataX.labels.length);
        ChartsData.ChartLineDataX.datasets[0].data.splice(1,ChartsData.ChartLineDataX.datasets[0].data.length);
        chart_linex.repaint();

        ChartsData.ChartLineDataY.labels.splice(1,ChartsData.ChartLineDataY.labels.length);
        ChartsData.ChartLineDataY.datasets[0].data.splice(1,ChartsData.ChartLineDataY.datasets[0].data.length);
        chart_liney.repaint();

        ChartsData.ChartLineDataZ.labels.splice(1,ChartsData.ChartLineDataZ.labels.length);
        ChartsData.ChartLineDataZ.datasets[0].data.splice(1,ChartsData.ChartLineDataZ.datasets[0].data.length);
        chart_linez.repaint();
    }


    RowLayout {
        id: baseGrid
        anchors.fill: parent
        anchors.margins: margin

        // 1. oszlop

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: firstColWidth

            ColumnLayout {
                anchors.fill: parent
                id: firstColoumn

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

                // Oszlopba rendezett további elemek
                ColumnLayout {
                    id: currentStateId
                    anchors.top: greenCheckBox.bottom
                    anchors.margins: margin
                    Text { text: " X: " + currentState.x.toFixed(3) + " m/s^2"  }
                    Text { text: " Y: " + currentState.y.toFixed(3) + " m/s^2"  }
                    Text { text: " Z: " + currentState.z.toFixed(3) + " m/s^2"  }
                    Text { text: " T: " + currentState.temp.toFixed(3) + " °C"  }
                    Text { text: " Nyomógomb: " + (currentState.button !== false ? "Lenyomva":"Nincs lenyomva") }
                }

                Text {
                    id:serialLog
                    anchors.top:currentStateId.bottom
                    anchors.margins: margin
                    text: "Soros port szöveges log:";
                }

                // Soros port log scrollozható szöveggel
                ScrollView {
                    anchors.top:serialLog.bottom
                    anchors.bottom: firstColoumn.bottom
                    anchors.margins: margin
                    Layout.fillHeight: true
                    Layout.maximumWidth: firstColWidth-margin


                    // Itt a szöveges logok listája.
                    ListView {
                        id: logHistoryList
                        model: logModel
                        delegate: Row {
                            Text { text: modelData }
                        }
                        // Folyamatos scroll
                        onCountChanged: {
                            logHistoryList.currentIndex = logHistoryList.count - 1;
                        }
                    }
                }
            }
        }

        // 2. oszlop

        GroupBox
        {

            Layout.fillHeight:true
            ColumnLayout
            {
                Layout.fillHeight:true
                GroupBox
                {
                   width: graphsWidth
                   height: graphsHeight
                   title:"A panel:"
                   anchors.margins: margin
                   Image
                    {
                        source: "\disc.jpg"
                        anchors.margins: margin

                        transform:
                        [
                            Rotation { origin.x: (175)*factorx/2; origin.y: (275)*factory/2; axis { x: 0; y: 1; z: 0 } angle: (currentState.x.toFixed(0)*9) },
                            Rotation { origin.x: (175)*factorx/2; origin.y: (275)*factory/2; axis { x: 1; y: 0; z: 0 } angle: (currentState.y.toFixed(0)*9) }
                        ]
                        smooth: true
                    }
                }

                GroupBox
                {
                    width: graphsWidth
                    height: graphsHeight
                    title:"X irányú gyorsulás:"
                    Chart
                    {
                        id: chart_linex;
                        width: graphsWidth
                        height: graphsHeight
                        chartAnimated: false;
                        chartData: ChartsData.ChartLineDataX;
                        chartType: Charts.ChartType.LINE;
                    }
                }

            }
        }

        // 3. oszlop

        GroupBox
        {

            Layout.fillHeight:true
            ColumnLayout
            {
                Layout.fillHeight:true
                GroupBox
                {
                    width: graphsWidth
                    height: graphsHeight
                    title:"Y irányú gyorsulás:"
                    Chart
                    {
                        id: chart_liney;
                        width: graphsWidth
                        height: graphsHeight
                        chartAnimated: false;
                        chartData: ChartsData.ChartLineDataY;
                        chartType: Charts.ChartType.LINE;
                    }
                }

                GroupBox
                {
                    width: graphsWidth
                    height: graphsHeight
                    title:"Z irányú gyorsulás:"
                    Chart
                    {
                        id: chart_linez;
                        width: graphsWidth
                        height: graphsHeight
                        chartAnimated: false;
                        chartData: ChartsData.ChartLineDataZ;
                        chartType: Charts.ChartType.LINE;
                    }
                }

            }
        }
    }
}
