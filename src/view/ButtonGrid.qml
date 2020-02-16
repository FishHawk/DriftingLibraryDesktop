import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

GridView {
    id: grid

    property int cellSize: 180

    signal selected(string chapterIndex)

    cellWidth: 200 + 20
    cellHeight: 50 + 20
    clip: true
    delegate: delegateComponent

    Component{
        id: delegateComponent
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            Button {
                anchors.centerIn: parent
                width: 200
                height: 50
                Label {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    text: modelData
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: selected(index)
                }
            }
        }
    }
}