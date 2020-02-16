import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

GridView {
    id: grid

    property int cellSize: 240

    cellWidth: cellSize + 20
    cellHeight: cellSize/3*4 + 20 + 20
    clip: true
    model: preview.images
    delegate: delegateComponent

    Component {
        id: delegateComponent
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            Image {
                x: 10; y: 10
                width: cellSize; height: cellSize/3*4
                sourceSize.width: width; sourceSize.height: height
                asynchronous: true
                fillMode: Image.PreserveAspectFit
                smooth: false
                source: preview.url + modelData
            }
            Label {
                x: 10 ; y: 10 + cellSize/3*4
                width: cellSize; height: 20
                horizontalAlignment: Text.AlignHCenter
                text: index + 1
            }
            MouseArea {
                anchors.fill: parent
                onClicked: chapterChoosed(0, 0, index)
            }
        }
    }
}