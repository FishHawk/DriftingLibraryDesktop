import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Backend 1.0

GridView {
    id: grid
    property int cellSize: 180
    signal mangaChoosed(var mangaSummary)

    cellWidth: cellSize + 20
    cellHeight: cellSize/3*4 + 20 + 20
    clip: true

    delegate: Item {
        width: grid.cellWidth; height: grid.cellHeight
        Image {
            x: 10; y: 10
            width: cellSize; height: cellSize/3*4
            sourceSize.width: width; sourceSize.height: height
            asynchronous: true
            fillMode: Image.PreserveAspectFit
            smooth: false
            source: thumb
        }
        Label {
            x: 10 ; y: 10 + cellSize/3*4
            height: 20
            text: title
        }
        MouseArea {
            anchors.fill: parent
            onClicked: mangaChoosed(title)
        }
    }
}